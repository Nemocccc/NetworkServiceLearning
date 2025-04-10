
""" 这里可以写一下接收和发送的函数 用来测试通信"""

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

    


    if __name__ == "__main__":
        pass