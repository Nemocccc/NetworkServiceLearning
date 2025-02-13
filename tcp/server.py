import socket
import threading



class tcpServer():
    def __init__(self, host = '127.0.0.1', port=12345):
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_address = (host, port)
        self.server_socket.bind(self.server_address)
        self.server_socket.settimeout(10)
        self.server_socket.listen(5)
        self.stop = False
        self.threads = []

    def Start(self):
        print(f"TCP Server is running on {self.server_address}")
        print("================================================")

        while not self.stop:
            try: 
                client_socket, client_address = self.server_socket.accept()
                print(f"\nConnection from {client_address[0]}:{client_address[1]}\n")
                thread = threading.Thread(target=self.run, args=(client_socket, client_address))
                self.threads.append(thread)
                thread.start()
            except socket.timeout:
                self.Stop()
                # break

    def run(self, client_socket, client_address):
        while True:
            data = client_socket.recv(4096)    #recv方法会一直阻塞进程，直到client发送的数据溢出4096或者client关闭连接（数据传输通道？），导致沾包。

            if not data:
                print("Connection close")
                break

            print(f"Received data without decode: \n {data}")
            # print(f"Received data decode to ASCII: \n {data.decode('ASCII')}") # UTF-8是ascii超集，无法解码
            print(f"Received data decode to UTF-8: \n {data.decode('UTF-8')}")
            print(f"Received data decode to latin1: \n {data.decode('latin1')}") # 乱码

            response = "Hello from server"
            client_socket.sendall(response.encode('UTF-8'))

    def Stop(self):
        print("Stop function is called, server closing")
        for thread in self.threads:
            thread.join()
        self.stop = True
        self.server_socket.close()


if __name__ == '__main__':
    server = tcpServer()
    server.Start()
    # server.Stop()
    print("Server is closed")