import socket
import json
import random
import time

class UDPClient:
    def __init__(self, host, port):
        self.server_address = (host, port)
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.sock.settimeout(5)
        self.buffer = b''

    def _receive_json(self):
        while True:
            try:
                data, _ = self.sock.recvfrom(4096)
                if not data:
                    return None
                self.buffer += data
                if b'\n' in self.buffer:
                    line, self.buffer = self.buffer.split(b'\n', 1)
                    # print(f"Received data: {line.decode()}")  # 增加调试信息
                    try:
                        return json.loads(line.decode())
                    except json.JSONDecodeError as e:
                        print(f"JSONDecodeError: {e}")
                        self.buffer = b''  # 清空缓冲区
                        continue
            except socket.timeout:
                print("数据接收超时")
                return None
            except ConnectionResetError:
                print("主机关闭连接")
                return None

    def send_command(self, command):
        # print(f"Sending command: {command}")  # 增加调试信息
        self.sock.sendto(command.encode() + b'\n', self.server_address)
        return self._receive_json()

    def close(self):
        self.sock.close()

if __name__ == '__main__':
    udp = UDPClient('127.0.0.1', 12345)
    directions = ['up', 'down', 'left', 'right', 'upleft', 'upright', 'downleft', 'downright']
    
    try:
        while True:
            random.seed(time.time())
            command = random.choice(directions)
            response = udp.send_command(command)
            if response is None:
                break
            print(f"Sent command: {command}")
            print(f"Received response: {response}")
            time.sleep(0.1)  # 每隔100毫秒发送一次命令
    except KeyboardInterrupt:
        print("测试中断")
    finally:
        udp.close()