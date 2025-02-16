### 运行方法

```bash
g++ -c -o Snake8Dir.o Snake8Dir.cpp -I./tcp
g++ -c -o tcp/SnakeTcp.o tcp/SnakeTcp.cpp -I./tcp
g++ -o Snake Snake8Dir.o tcp/SnakeTcp.o -lws2_32
./Snake

python tcp/SnackTcpClient.py
```