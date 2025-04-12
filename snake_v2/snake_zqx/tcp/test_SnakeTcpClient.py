import socket
import json
import threading
import random
import time

class TCPClient:
    def __init__(self, host, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((host, port))
        self.sock.settimeout(5)
        self.buffer = b''

    def _receive_json(self):
        while True:
            if b'\n' in self.buffer:
                line, self.buffer = self.buffer.split(b'\n', 1)
                return json.loads(line.decode())
            try:
                data = self.sock.recv(4096)
                if not data:
                    return None
            except socket.timeout:
                print("数据接收超时")
                return None
            except ConnectionResetError:
                print("主机关闭连接")
                return None
            self.buffer += data

    def send_command(self, command):
        try:
            self.sock.sendall(command.encode() + b'\n')
        except ConnectionResetError:
            print("主机关闭连接")
            return None
        return self._receive_json()

    def close(self):
        self.sock.close()

if __name__ == '__main__':
    tcp = TCPClient('127.0.0.1', 12345)
    directions = ['up', 'down', 'left', 'right', 'upleft', 'upright', 'downleft', 'downright']
    
    try:
        while True:
            random.seed(time.time())
            command = random.choice(directions)
            response = tcp.send_command(command)
            if response is None:
                break
            print(f"Sent command: {command}")
            print(f"Received response: {response}")
            

            # 取出 game_over 的值
            game_over = response['game_over']
            print("game_over:", game_over)

            # 取出 snake 的值，snake 是一个包含多个字典的列表
            snake = response['snake']
            snake_body = []
            #print("snake:", snake)
            for segment in snake:
                snake_body.append(tuple(segment.values()))
            print(snake_body)

            # 取出 foods 的值，foods 是一个包含多个字典的列表
            foods = response['foods']
            all_food_pos = []
            
            for segment in foods:
                all_food_pos.append(tuple(segment.values()))
            print(all_food_pos)

            # 取出 map 的值，map 是一个字典
            game_map = response['map']
            width = game_map['width']
            height = game_map['height']
            walls = game_map['walls']
            print("Map width:", width)
            print("Map height:", height)
            print("Walls:", walls)

            all_walls = []
            for segment in walls:
                all_walls.append(tuple(segment.values()))
            print(all_walls)
            # 取出 score 的值
            score = response['score']
            print("score:", score)

            
            time.sleep(0.1)  # 每隔10毫秒发送一次命令
    except KeyboardInterrupt:
        print("测试中断")
    finally:
        tcp.close()