### gRPC

[gRPC框架官方教程](https://grpc.org.cn/docs/languages/python/basics/)

![alt text](static/image.png)

-  四种服务(流式与一元)：
```proto
rpc SayHello(HelloRequest) returns (HelloResponse);
...
rpc SayHello(stream HelloRequest) returns (stream HelloResponse);
// 区别在于stream关键字
// rpc client(client-data-structure) returns (server-data-structure) {}
```

1. **安装grpc**
  ```powershell
  pip install grpcio
  pip install grpcio-tools
  ```

2. **简单服务定义**
   *vscode推荐下载vscode-proto3插件*
   ```proto
   syntax 'proto3'; // 指定proto buffers版本为proto3

   package Service // package用于创建命名空间，相当于c++的namespace

   //此外，还有option关键字用于指定protoc编译器的某些行为

   service ServiceName {
    //method
    rpc client(client-data-structure) returns (server-data-structure) {}
   }

   message client-data-structure {
    int32 interval = 1;
    // 这里的1并不是internal的默认指，而是internal在client-data-structure这个message的编号
    bool var1 = 2;
    repeated int32 IntArr = 3; // 用repeated关键字定义数组
    ...
   }

    ...
    ```

3. 利用proto根据.proto文件自动生成python文件
   ```powershell
   python -m gprc_tools.protoc \
    -I{dir-where-protofiles-in} \
    --python_out={output-files-of-.py-files} \
    --pyi_out={output-files-of-.pyi-files} \
    --grpc_python_out={grpc-python-code} \
    {relative-path-of-the-.proto-files}
   ```
   示例：
   ```powershell
   python -m grpc_tools.protoc -Igrpc/example/custom/path=../../protos --python_out=. --grpc_python_out=. ../../protos/route_guide.proto
   ```
  

4. 利用生成的{}_pb2_grpc.py和{}_pb2.py编写服务端和客户端代码
  - 客户端(server.py)：
    ```python
    import grpc
    from concurrent import futures

    import {}_pb2_grpc
    import {}_pb2

    #例如 对应try.proto, server.py需要实现 class TryServicer({}_pb2_grpc.TryServicer) 用大驼峰命名
    #这个class需要继承grpc_tools自动实现的类{proto文件名大驼峰}
    class {}Servicer({}_pb2_grpc.{}Servicer):
      #在类里面实现你在.proto文件里面写的功能
      #比如rpc FuncClient(Request) returns (Response)
      #你就要实现def FuncClient(self, request, context):
      #request里面包含的是你的请求，可以理解为message关键字定义的数据相当于一个json
      #context包含你的请求上下文，比如客户端的ip，定义响应状态，设置超时等，可以通过context设置。
      def FuncClient(self, request, context):
        return {}_pb2.{Client-data-structure}({key} = f"value: {value}")
        #我的理解是，{}_pb2_grpc.py定义的是服务的行为，{}_pb2.py定义的是数据的行为。
        #不同于python的data.{}={}的数据赋值形式，这里采用类函数的传入赋值，
        #而且没有position编码，你必须显式指定你的value赋值给哪个key，不然报错。


    def serve(): #服务
      server = grpc.server(futures.ThreadPoolExecutor(max_workers = 10)) # 创建server
      {}_pb2_grpc.add_{}Servicer_to_server(
        {}Servicer(), server
      ) # 这个add_{}_to_server被称为注册函数，用于将你实现的服务的类注册到grpc服务器商，并用创建的server进程池部署服务
      server.add_insecure_port("[::]:50051") # 监听所有50051端口
      server.start() # 启动服务
      server.wait_for_termination() # 这句代码用于在服务器显式关闭的时候关闭服务，但是感觉用处不大，直接stop(times)感觉更实用。

    if __name__ == '__main__':
      server()
    ```
    这是最简单的服务端代码样板，实际需要自己按需拓展。
    <br>
  - 客户端代码(client.py):
    ```python
    import grpc
    import {}_pb2_grpc
    import {}_pb2
    #主要实现run()方法，对服务端定义的接口进行请求。
    run():
      channel = grpc.insecure_channel("{}:50051") # 定义通道
      stub = {}_pb2_grpc.{}Stub(channel) # 对于服务中的每个方法，编译器都会使用相同名称向 stub 对象添加一个对应的属性。，见下面
      response = stub.FuncClient({}_pb_2.Client_data_structure({key} = {value}))
      # 利用服务端的FuncClient服务进行请求.将返回的数据保存到response变量中
      print(response.{key}) # 对response进行操作。

    if __name__ == '__main__':
      run()
    ```

5. 启动服务：
   ```bash
   python server.py
   // 新开一个终端启动客户端
   python client.py
   ```


### tcp

1. server.py
  ```python
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)   # 用SOCK_STREAM创建套接字
    server_address = (host, port)                                       # 
    server_socket.bind(self.server_address)                             # 绑定服务地址
    server_socket.listen()                                              # 监听

    while True:
      client_socket, client_address = self.server_socket.accept()              # 接受连接
      data = client_socket.recv(4096)
      response = ""
      client_socket.sendall(response.encode('UTF-8'))
      # client_socket.close() 如果执行这个，client在recv方法之后的sendall因为被终止无法执行。
      if not data:
        server_socket.close()
  ```