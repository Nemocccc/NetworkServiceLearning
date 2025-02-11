import socket

def tcp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    server_address = ('localhost', 12345)

    try:
        client_socket.connect(server_address)
        print(f"Connect to {server_address}")

        message = "Hello from 客户端"
        client_socket.sendall(message.encode('UTF-8'))

        message = "\n另一条"
        client_socket.sendall(message.encode('UTF-8'))
        
        response = client_socket.recv(4096)    # 目前不清楚，似乎client端的recv方法会中断server的recv方法，让recv返回data
        print(f"receive response: {response}")

        message = "这条消息不会粘前面的包，server端进第二次循环了。"
        client_socket.sendall(message.encode('UTF-8'))

        response = client_socket.recv(4096)        # 注释掉之后，server端的recv方法会一直阻塞，不返回data，
                                                     # if not data:判断语句失效不被执行，直到stop()方法强制关闭连接并报错
        print(f"receive response: {response}")
    finally:
        client_socket.close()

if __name__ == '__main__':
    tcp_client()