import grpc
import logging
from concurrent import futures

import try_pb2_grpc
import try_pb2

class TryServicer(try_pb2_grpc.TryServicer):
    def tryClient(self, request, response):
        return try_pb2.Response(message = f"hello from server: {request.name}")


class serve():
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    try_pb2_grpc.add_TryServicer_to_server(
        TryServicer(), server
    )
    server.add_insecure_port("[::]:50051")
    server.start()
    server.wait_for_termination()


if __name__ == '__main__':
    logging.basicConfig()
    serve()