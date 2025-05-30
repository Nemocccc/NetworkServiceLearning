import gymnasium as gym
import torch
import numpy as np
from torch.distributions import Categorical
import torch.nn as nn
import time  # 用于控制游戏速度
import random  # 添加 random 模块的导入
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
    device = torch.device("cpu")  # 使用 CPU 运行，避免 CUDA 问题

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
    rewards = []  # 用于存储每局的奖励

    for ep in range(total_episodes):
        # 启动客户端 接收信息
        tcp = TCPClient('127.0.0.1', 12345)
        try:
            # 初始化
            action = random.randint(0, 3)
            command = action_interface(action)
            env.current_direction = action

            response = tcp.send_command(command)
            if response is None:
                break

            all_food_pos, snake_body, all_wall_pos, steps, reward, terminated, truncated, _ = decode(response)

            # 初始化获取 obs
            obs = obs_interface(all_food_pos, snake_body, all_wall_pos)

            while not (terminated or truncated):
                # 转换观测到 tensor
                obs_tensor = torch.FloatTensor(obs).to(device)
                # 获取动作
                with torch.no_grad():
                    action = agent.get_action_and_value(obs_tensor)[0].item()
                    if action == get_opposite(env.current_direction):
                        action = env.current_direction  # 保持原方向
                    env.current_direction = action
                # 将动作发给 c++ 执行 然后获取 obs 和 reward
                command = action_interface(action)
                response = tcp.send_command(command)
                print(f"send:{command}")
                all_food_pos, snake_body, all_wall_pos, steps, reward, terminated, truncated, _ = decode(response)
                obs = obs_interface(all_food_pos, snake_body, all_wall_pos)

            # 记录本局数据
            episode_lengths.append(steps)
            rewards.append(reward)
            print(f"Episode {ep + 1}/{total_episodes} |"
                  f"Length: {steps} steps"
                  f"Score: {reward} ")

            # 在这里添加重置逻辑
            if not (ep == total_episodes - 1):  # 如果不是最后一局
                # 发送重置命令给服务端
                reset_command ='reset'  
                response = tcp.send_command(reset_command)
                print(f"send:{reset_command}")
                if response is None:
                    print("重置命令响应失败")
                    break
                # 重新初始化环境相关变量
                action = random.randint(0, 3)
                command = action_interface(action)
                env.current_direction = action
                response = tcp.send_command(command)
                all_food_pos, snake_body, all_wall_pos, steps, reward, terminated, truncated, _ = decode(response)
                obs = obs_interface(all_food_pos, snake_body, all_wall_pos)

        except KeyboardInterrupt:
            print("测试中断")
        finally:
            tcp.close()

    # 输出统计结果
    print("\n=== Test Results ===")
    print(f"Average Reward: {np.mean(rewards):.2f} ± {np.std(rewards):.2f}")
    print(f"Average Episode Length: {np.mean(episode_lengths):.2f} steps")
    print(f"Max Reward: {np.max(rewards)}")
    print(f"Min Reward: {np.min(rewards)}")
    env.close()


if __name__ == "__main__":
    # 配置参数
    test_config = {
        "env_id": "Snake-v0",  
        "model_path": r"saved_models\Snake-v0__ppo_train_agent_vector__1__1744441810/model_4850.pth",  # 模型路径
        "test_episodes": 10,  # 测试局数
        "render_delay": 0.08  # 渲染延迟
    }

    test_model(test_config)