import grpc
import test_pb2
import test_pb2_grpc

def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = test_pb2_grpc.TestStub(channel)
    responseHello = stub.SayHello(test_pb2.Hello(name="client"))
    print("Client received: " + responseHello.name)
    responsePackage = stub.GetPackage(test_pb2.PackageIndex(Index=1))
    print("Client received: " + str(responsePackage.uid))
    for items in responsePackage.IntArr:
        print("Client received: " + str(items))
    print("Client received: " + responsePackage.discription)
    print("Client received: " + str(responsePackage.status))
    responseClient = stub.GetClientInfo(test_pb2.Hello(name="client"))
    print("Client received: " + responseClient.Info)

if __name__ == '__main__':
    run()