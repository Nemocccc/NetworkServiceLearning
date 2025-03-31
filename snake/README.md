### 运行方法

#### Tcp
```bash
g++ -c -o Snake8Dir.o Snake8Dir.cpp -I./tcp
g++ -c -o tcp/SnakeTcp.o tcp/SnakeTcp.cpp -I./tcp
g++ -c -o udp/SnakeUdp.o udp/SnakeUdp.cpp -I ./udp
g++ -o Snake Snake8Dir.o tcp/SnakeTcp.o udp/SnakeUdp.o -lws2_32


./Snake.exe tcp
// 新开终端
python tcp/SnakeTcpClient.py

./Snake.exe udp
// 新开终端
python udp/SnakeUdpClient.py
```
