import gymnasium as gym
import torch
import numpy as np
from torch.distributions import Categorical
import torch.nn as nn
import time  # 用于控制游戏速度

import sys
import os
# 获取当前脚本所在的目录
current_dir = os.path.dirname(os.path.abspath(__file__))
# 获取上一层目录
parent_dir = os.path.dirname(current_dir)
# 将上一层目录添加到 sys.path 中
sys.path.append(parent_dir)

from envs import *

# 确保与训练时相同的网络结构 即PPO算法中的网络结构
def layer_init(layer, std=np.sqrt(2), bias_const=0.0):
    torch.nn.init.orthogonal_(layer.weight, std)
    torch.nn.init.constant_(layer.bias, bias_const)
    return layer

class Agent(torch.nn.Module):
    def __init__(self, envs):
        super().__init__()
        self.critic = nn.Sequential(
            layer_init(nn.Linear(np.array(envs.single_observation_space.shape).prod(), 64)),
            nn.Tanh(),
            layer_init(nn.Linear(64, 64)),
            nn.Tanh(),
            layer_init(nn.Linear(64, 1), std=1.0),
        )
        self.actor = nn.Sequential(
            layer_init(nn.Linear(np.array(envs.single_observation_space.shape).prod(), 64)),
            nn.Tanh(),
            layer_init(nn.Linear(64, 64)),
            nn.Tanh(),
            layer_init(nn.Linear(64, envs.single_action_space.n), std=0.01),
        )

    def get_value(self, x):
        return self.critic(x)

    def get_action_and_value(self, x, action=None):
        logits = self.actor(x)
        probs = Categorical(logits=logits)
        if action is None:
            action = probs.sample()
        return action, probs.log_prob(action), probs.entropy(), self.critic(x)

def test_model(config):
    # 初始化环境
    env = gym.make(config["env_id"], render_mode="human") 
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    
    # 创建与训练时相同的环境结构（用于获取空间信息）
    dummy_env = gym.make(config["env_id"])
    dummy_env = gym.vector.SyncVectorEnv([lambda: dummy_env])
    
    # 加载训练好的模型
    agent = Agent(dummy_env).to(device)
    agent.load_state_dict(torch.load(config["model_path"], map_location=device), strict=False)
    agent.eval()
    
    dummy_env.close()

    # 测试参数
    total_episodes = config["test_episodes"]
    total_rewards = []
    episode_lengths = []
    
    for ep in range(total_episodes):
        obs, _ = env.reset()
        episode_reward = 0
        steps = 0
        terminated = False
        truncated = False
        
        while not (terminated or truncated):
            # 转换观测到tensor
            obs_tensor = torch.FloatTensor(obs).to(device)
            
            # 获取动作
            with torch.no_grad():
                action = agent.get_action_and_value(obs_tensor)[0].item()

            # 执行动作
            obs, reward, terminated, truncated, _ = env.step(action)
            env.render()
            # 更新统计
            episode_reward += reward
            steps += 1
            
            # 添加延迟方便观察
            time.sleep(config["render_delay"])
            
            
        # 记录本局数据
        total_rewards.append(episode_reward)
        episode_lengths.append(steps)
        print(f"Episode {ep+1}/{total_episodes} | "
              f"Reward: {episode_reward:.1f} | "
              f"Length: {steps} steps")
    
    # 输出统计结果
    print("\n=== Test Results ===")
    print(f"Average Reward: {np.mean(total_rewards):.2f} ± {np.std(total_rewards):.2f}")
    print(f"Average Episode Length: {np.mean(episode_lengths):.2f} steps")
    print(f"Max Reward: {np.max(total_rewards)}")
    print(f"Min Reward: {np.min(total_rewards)}")
    env.close()

if __name__ == "__main__":
    # 配置参数
    test_config = {
        "env_id": "Snake-v0",          #环境ID
        "model_path": r"saved_models\Snake-v0__ppo_train_agent_vector__1__1744441810/model_4300.pth",  # 模型路径
        "test_episodes": 1,          #测试局数
        "render_delay": 0.08          #渲染延迟
    }
    test_model(test_config)