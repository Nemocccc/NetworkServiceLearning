import socket
import threading
import time



# def tcp_server():
#     server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

#     server_address = ('localhost', 12345)
#     server_socket.bind(server_address)

    # server_socket.listen()
    # print(f"TCP Server is running on {server_address}")

    # try:
    #     while True:
    #         client_socket, client_address = server_socket.accept()
    #         print(f"Connection from {client_address}")

    #         data = client_socket.recv(4096)
    #         print(f"Received data: \n {data}")

    #         response = "Hello from server"
    #         client_socket.sendall(response.encode('UTF-8'))

    #         client_socket.close()
    # finally:
    #     server_socket.close()


class tcpServer():
    def __init__(self, host = '127.0.0.1', port=12345):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_address = (host, port)
        self.server_socket.bind(self.server_address)
        self.server_socket.listen()
        self.stop = True

    def Start(self):
        self.stop = False
        threading.Thread(target=self.run).start()

    def run(self):
        print(f"TCP Server is running on {self.server_address}")
        print("================================================")
        client_socket, client_address = self.server_socket.accept()
        print(f"\nConnection from {client_address[0]}:{client_address[1]}\n")

        while not self.stop:

            data = client_socket.recv(4096)    #recv方法会一直阻塞进程，直到client发送的数据溢出4096或者client关闭连接（数据传输通道？），导致沾包。
            print(f"Received data without decode: \n {data}")
            # print(f"Received data decode to ASCII: \n {data.decode('ASCII')}") # UTF-8是ascii超集，无法解码
            print(f"Received data decode to UTF-8: \n {data.decode('UTF-8')}")
            print(f"Received data decode to latin1: \n {data.decode('latin1')}") # 乱码

            response = "Hello from server"
            client_socket.sendall(response.encode('UTF-8'))

            if not data:
                print("Connection close")
                self.stop = True
                self.server_socket.close()
                break

    def Stop(self):
        self.stop = True
        self.server_socket.close()


if __name__ == '__main__':
    server = tcpServer()
    server.Start()
    time.sleep(10)
    server.Stop()
    print("Server is closed")