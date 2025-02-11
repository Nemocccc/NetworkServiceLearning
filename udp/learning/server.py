import socket

def udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = ('localhost', 12345)
    server_socket.bind(server_address)

    print(f"server is running on {server_address}")

    try:
        while True:
            data, address = server_socket.recvfrom(4096)
            print(f"Received {data} from {address}")

            response = "Hello, client"
            server_socket.sendto(response.encode(), address)

            if not data:
                print("connection close")
                break
    finally:
        server_socket.close()

if __name__ == '__main__':
    udp_server()