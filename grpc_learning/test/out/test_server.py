import test_pb2_grpc
import test_pb2

import grpc
from concurrent import futures
]

class TestServicer(test_pb2_grpc.TestServicer):
    def SayHello(self, request, context):
        return test_pb2.Hello(name="server")

    def GetPackage(self, request, context):
        return test_pb2.PackageInfo(
            uid = 114,
            IntArr = [1, 2, 3],
            discription = "PackageInfo",
            status = True
        )

    def GetClientInfo(self, request, context):
        return test_pb2.ClientInfo(Info = str(context))


def serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    test_pb2_grpc.add_TestServicer_to_server(
        TestServicer(), server
    )
    server.add_insecure_port('[::]:50051')
    server.start()
    print("Server started")
    server.wait_for_termination()

if __name__ == '__main__':
    serve()