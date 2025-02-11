import socket 
import time

def udp_client():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    server_address = ('localhost', 12345)

    try:
        message = [f"message {x} from client" for x in range(1000)]    # udp丢包不好复现，需要特别大量的数据才能观测到丢包
        for msg in message:
            client_socket.sendto(msg.encode('UTF-8'), server_address)

        response, server_address_return = client_socket.recvfrom(4096)
        print(f"received data:{response} from {server_address_return}")
    finally:
        client_socket.sendto("exit".encode('UTF-8'), server_address)
        client_socket.close()

if __name__ == '__main__':
    udp_client()