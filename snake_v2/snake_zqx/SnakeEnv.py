# snake_env.py
import socket
import json
import numpy as np
#import grpc
from gymnasium import Env
from gymnasium.spaces import Discrete, Box, Dict
#from grpc import RpcError
from client import *
# 与C++代码中定义的常量一致
MAP_WIDTH = 29
MAP_HEIGHT = 26
MAX_LENGTH = 10
MAX_FOOD_NUMBERS = 5
BUFFER_SIZE = 4096

# import subprocess

# # 使用 subprocess.run()
# subprocess.run(["Snake.exe"])

# # # 或者使用 subprocess.Popen()
# # process = subprocess.Popen(["example.exe"])
# # process.wait()


class UDPClient:
    def __init__(self, host, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_addr = (host, port)
        self.sock.settimeout(2)

    def send_command(self, command):
        self.sock.sendto(command.encode(), self.server_addr)
        try:
            data, _ = self.sock.recvfrom(BUFFER_SIZE)
            return json.loads(data.decode())
        except socket.timeout:
            return None

    def close(self):
        self.sock.close()


class SnakeEnv(Env):
    metadata = {'render_modes': ['human']}

    def __init__(self, comm_type='tcp', host='localhost', port=12345):
        super().__init__()
        self.comm_type = comm_type
        self.host = host
        self.port = port
        self.client = None
        self.last_score = 0

        # 定义动作空间（8个方向）
        self.action_space = Discrete(8)

        # 定义观察空间
        inf=np.inf
        self.observation_space = Box(-inf,inf,(10*10))

        self._init_client()

    def _init_client(self):
        if self.comm_type == 'tcp':
            self.client = TCPClient(self.host, self.port)
        elif self.comm_type == 'udp':
            self.client = UDPClient(self.host, self.port)
        # elif self.comm_type == 'grpc':
        #     self.client = GrpcClient(self.host, self.port)
        else:
            raise ValueError(f"Unsupported protocol: {self.comm_type}")

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)
        self.last_score = 0

        response = self.client.send_command("reset")
        obs = self._parse_json_state(response)

        return obs, {}

    def step(self, action):
        direction = self._action_to_str(action)

        response = self.client.send_command(direction)
        obs = self._parse_json_state(response)
        done = response.get('game_over', True) if response else True
        reward = response.get('score', 0) - self.last_score if response else 0
        self.last_score = response.get('score', 0) if response else 0

        return obs, reward, done, False, {}

    def _action_to_str(self, action):
        directions = [
            'up', 'down', 'left', 'right',
            'upleft', 'upright', 'downleft', 'downright'
        ]
        return directions[action]

    def _parse_json_state(self, data):
        if not data:
            return self.observation_space.sample()

        # 解析蛇身坐标
        snake = np.zeros((MAX_LENGTH, 2), dtype=np.int32)
        snake_segs = data.get('snake', [])[:MAX_LENGTH]
        for i, seg in enumerate(snake_segs):
            snake[i] = [seg['x'], seg['y']]

        # 解析食物坐标
        foods = np.zeros((MAX_FOOD_NUMBERS, 2), dtype=np.int32)
        food_items = data.get('foods', [])[:MAX_FOOD_NUMBERS]
        for i, food in enumerate(food_items):
            foods[i] = [food['x'], food['y']]

        # 解析墙壁信息
        walls = np.zeros((MAP_HEIGHT, MAP_WIDTH), dtype=np.int8)
        for wall in data.get('map', {}).get('walls', []):
            x, y = wall['x'], wall['y']
            if 0 <= x < MAP_WIDTH and 0 <= y < MAP_HEIGHT:
                walls[y][x] = 1

        return {
            'snake': snake,
            'foods': foods,
            'score': np.array(data.get('score', 0), dtype=np.int32),
            'walls': walls
        }

    def close(self):
        if self.client:
            self.client.close()


# 示例用法
if __name__ == "__main__":
    # TCP测试
    
    env = SnakeEnv(comm_type='tcp')
    obs, _ = env.reset()
    print("TCP Reset Observation:", obs)
    print(env.action_space.sample())
    obs, reward, done, _, _ = env.step(env.action_space.sample())
    print("TCP Step Result:", obs, reward, done)
    env.close()
