import socket
import json
import threading
import random
import time

class TCPClient:
    def __init__(self, host, port):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.sock.connect((host, port))
        self.sock.settimeout(0.1)
        self.buffer = b''

    def _receive_json(self):
        while True:
            if b'\n' in self.buffer:
                line, self.buffer = self.buffer.split(b'\n', 1)
                return json.loads(line.decode())
            try:
                data = self.sock.recv(1024)
                if not data:
                    return None
            except socket.timeout:
                print("数据接收超时")
                return None
            self.buffer += data

    def send_command(self, command):
        self.sock.sendall(command.encode() + b'\n')
        return self._receive_json()

    def close(self):
        self.sock.close()

if __name__ == '__main__':
    tcp = TCPClient('127.0.0.1', 12345)
    directions = ['up', 'down', 'left', 'right', 'upleft', 'upright', 'downleft', 'downright']
    
    try:
        while True:
            command = random.choice(directions)
            response = tcp.send_command(command)
            print(f"Sent command: {command}, Received response: {response}")
            time.sleep(0.01)  # 每隔10毫秒发送一次命令
    except KeyboardInterrupt:
        print("测试中断")
    finally:
        tcp.close()