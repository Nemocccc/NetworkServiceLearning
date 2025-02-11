import socket 

def udp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = ('localhost', 12345)

    try:
        message = "Hello from client"
        client_socket.sendto(message.encode('UTF-8'), server_address)

        response, server_address_return = client_socket.recvfrom(4096)
        print(f"received data:{response} from {server_address_return}")
    finally:
        client_socket.sendto("close".encode('UTF-8'), server_address)
        client_socket.close()

if __name__ == '__main__':
    udp_client()