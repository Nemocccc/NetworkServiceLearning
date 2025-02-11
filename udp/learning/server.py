import socket

def udp_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = ('localhost', 12345)
    server_socket.bind(server_address)

    server_socket.settimeout(10)
    print(f"server is running on {server_address}")

    try:
        while True:
            data, address = server_socket.recvfrom(1024)
            print(f"Received {data} from {address}")

            response = "Hello, client"
            server_socket.sendto(response.encode(), address)
    except ConnectionResetError:
        print("Client closed the connection")
    except TimeoutError:
        print("Timeout occurred")
    finally:
        print("server is closing")
        server_socket.close()

if __name__ == '__main__':
    udp_server()