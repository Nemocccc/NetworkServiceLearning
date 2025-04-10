import grpc
import try_pb2_grpc
import try_pb25230q5320w



def run():
    with grpc.insecure_channel('localhost:50051') as channel:
        stub = try_pb2_grpc.TryStub(channel)
        responce = stub.tryClient(try_pb2.Request(name = "client"))
        print("received:" + responce.message)


if __name__ == '__main__':
    run()