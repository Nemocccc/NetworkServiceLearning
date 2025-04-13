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

from Agent import *
from interface import *
from client import *

def test_model(config):
    # 初始化环境
    env = gym.make(config["env_id"], render_mode="human") 
    device = torch.device("cuda" if torch.cuda.is_available() else "cpu")
    
    # 创建智能体
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
    episode_lengths = []
    
    for ep in range(total_episodes):
        # 启动客户端 接收信息 此处需要填写
        tcp = TCPClient('127.0.0.1', 12345)
        try:
            while True:
                # 初始化
                action = random.randint(1,3)
                command = action_interface(action)
                env.current_direction = action
                env.reset()
                response = tcp.send_command(command)
                if response is None:
                    break

                all_food_pos,snake_body, all_wall_pos,steps, reward, terminated, truncated,_ = decode(response)

                #初始化获取obs 
                obs = obs_interface(all_food_pos,snake_body, all_wall_pos)
                obs_trans(env = env,obs_grid= obs)
                env.render()

                while not (terminated or truncated):
                    # 转换观测到tensor
                    obs_tensor = torch.FloatTensor(obs).to(device)
                    # 获取动作
                    with torch.no_grad():
                        action = agent.get_action_and_value(obs_tensor)[0].item()
                        if action == get_opposite(env.current_direction):
                            action = env.current_direction  # 保持原方向
                        env.current_direction = action
                    #将动作发给c++ 执行 然后获取obs和reward  此处需要填写
                    command = action_interface(action)
                    response = tcp.send_command(command)
                    print(f"send:{command}")
                    all_food_pos,snake_body, all_wall_pos,steps, reward, terminated, truncated,_ = decode(response)

                    env.steps += 1
                    obs = obs_interface(all_food_pos, snake_body, all_wall_pos)
                    obs_trans(env = env,obs_grid= obs)
                    env.render()
                    
                # 记录本局数据
                episode_lengths.append(steps)
                print(f"Episode {ep+1}/{total_episodes} |"
                        f"Length: {steps} steps"
                        f"Score: {reward} ")

            # 输出统计结果
            print("\n=== Test Results ===")
            print(f"Average Reward: {np.mean(reward):.2f} ± {np.std(reward):.2f}")
            print(f"Average Episode Length: {np.mean(episode_lengths):.2f} steps")
            print(f"Max Reward: {np.max(reward)}")
            print(f"Min Reward: {np.min(reward)}")
            env.close()

        except KeyboardInterrupt:
            print("测试中断")
        finally:
            tcp.close()



if __name__ == "__main__":
    # 配置参数
    test_config = {
        "env_id": "Snake-v0",          #环境ID
        "model_path": "saved_models\Snake-v0__ppo_train_agent_vector__1__1744441810\model_4800.pth",  # 模型路径
        "test_episodes": 1,          #测试局数
        "render_delay": 0.08          #渲染延迟
    }
    
    test_model(test_config)