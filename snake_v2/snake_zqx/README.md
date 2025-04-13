### 文件说明

_cleanrl_: GitHub 下载的 cleanrl 库
_envs_： 使用 gym 库自定义的环境 设置文件在 Snake_v0.py 中
_runs_： 训练日志，训练完成后可以使用命令 tensorboard --logdir runs/ 打开
_saved_models_： 保存模型

_ppo_train_agent.py_： 使用 ppo 算法对智能体进行训练 直接运行即可 默认会保存模型
_test_agent.py_： 测试跑好的模型在通信时的效果
_interface.py_ : 接口文件 包括 解包、状态接口 和 动作接口
_test.py_： 草稿文件
_Agent.py_: 智能体的策略网络结构
_clinet.py_ : 存放 tcp 的客户端

#### 为防止难度过大导致智能体收敛困难 目前 python 中的场景比较简单

#### 目前 python 版 地图大小为 10\*10 食物最大数量为 1

### 运行方法

#### Tcp

```bash

g++ -c -o Snake8Dir.o Snake8Dir.cpp -I./tcp
g++ -c -o tcp/SnakeTcp.o tcp/SnakeTcp.cpp -I./tcp
g++ -c -o udp/SnakeUdp.o udp/SnakeUdp.cpp -I ./udp
g++ -o Snake Snake8Dir.o tcp/SnakeTcp.o udp/SnakeUdp.o -lws2_32


./Snake.exe tcp
// 新开终端
python test_agent_com.py

./Snake.exe udp
// 新开终端
python udp/SnakeUdpClient.py
```

整体逻辑：
c++完成初始化
循环：
c++发送 info 给 python 方
（info 包含 食物位置 蛇身体位置 墙位置 当前运动方向 当前步数 得分 是否结束 是否中断 其它信息）

    python方对info完成decode成为state
    python方将state输入get_action_and_value，获取next_action
    python对next_action 完成封装成为info
    python方将info发给c++
    c++对info完成解包
    c++执行next_action,并更新state
