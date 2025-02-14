import grpc
import snack_pb2
import snack_pb2_grpc


def interaction(stub):
    operate = input("Client input: ")
    GameData = stub.Interaction(snack_pb2.Operation(direction = operate))
    print("Client received: " + GameData.data)
    while !GameData.game_over:
        operate = input("Client input: ")
        GameData = stub.Interaction(snack_pb2.Operation(direction = operate))
        print("\nClient received: " + GameData.data)


def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = snack_pb2_grpc.SnackStub(channel)
    
    testOK = stub.TestConnect(snack_pb2.Hello(msg = "client"))
    print("Client received: " + testOK.msg)

    print("=====================start interaction=====================")
    interaction(stub)

if __name__ == '__main__':
    run()