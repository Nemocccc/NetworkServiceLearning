import gymnasium as gym
from gymnasium import spaces
import numpy as np
from matplotlib import pyplot as plt
from matplotlib import patches
import copy


GridSize = 10
MaxFood = 1
InitLength = 3
MaxLength = 6
WallNum = 0
RendMode = None

def get_opposite(action):
    opposites = {0:1, 1:0, 2:3, 3:2}
    return opposites[action]

# obs_grid 中  1为蛇身 2为食物 3为蛇头 0 为空闲格子
class SnakeEnv(gym.Env):
    metadata = {"render_modes": ['human', 'rgb_array'], "render_fps": 1}
    
    def __init__(self, grid_size=GridSize,max_food = MaxFood,init_length = InitLength,max_length = MaxLength,render_mode=RendMode,wall_num = WallNum):
        super(SnakeEnv, self).__init__()
        self.grid_size = grid_size
        self.render_mode = render_mode
        
        # 动作空间：4个方向（上0，下1，左2，右3）
        self.action_space = spaces.Discrete(4)
        
        # 观察空间：每个格子有4种状态（0:空, 1:蛇身, 2:食物, 3:蛇头）
        # 使用onehot编码
        inf=np.inf
        self.observation_space = gym.spaces.Box(-inf,inf,(grid_size,grid_size))

        # 初始化游戏参数
        self.snake_body = None
        self.food_pos = None
        self.current_direction = None
        self.steps = None
        self.max_steps = 100  # 防止无限循环
        
        self.init_length = init_length
        self.max_length = max_length
        self.max_food = max_food

        # 渲染相关
        self.fig = None
        self.ax = None

    def _get_obs(self):
        obs_grid = np.zeros((self.grid_size, self.grid_size), dtype=int)
        # 标记食物
        if self.food_pos is not None:
            obs_grid[self.food_pos[0], self.food_pos[1]] = 2
        # 标记蛇身
        for i, pos in enumerate(self.snake_body):
            # i== 0 时为蛇头
            obs_grid[pos[0], pos[1]] = 3 if i == 0 else 1
        return obs_grid

    def _generate_food(self):
        all_pos = set((i,j) for i in range(self.grid_size) for j in range(self.grid_size))
        snake_pos = set(tuple(pos) for pos in self.snake_body)
        available = list(all_pos - snake_pos)
        # 如果有可以获取的 那么随机从中选择一个返回
        return available[np.random.choice(len(available))] if available else None

    def reset(self, seed=None, options=None):
        super().reset(seed=seed)

        self.snake_body = []

        # 初始蛇：3节水平居中
        init_x  = (self.grid_size-2)//2
        init_y = (self.grid_size-2)//2



        for i in range(3):
            self.snake_body.append((init_x- i,init_y))

        self.current_direction = 1  # 初始方向向下
        self.food_pos = self._generate_food()
        self.steps = 0
        return self._get_obs(), {}

    def _get_opposite(self, action):
        opposites = {0:1, 1:0, 2:3, 3:2}
        return opposites[action]

    def step(self, action):
        # 处理无效动作
        if action == self._get_opposite(self.current_direction):
            action = self.current_direction  # 保持原方向
            
        # 更新方向
        self.current_direction = action
        
        # 计算新头部位置
        head_x, head_y = self.snake_body[0]
        if action == 0:    new_head = (head_x, head_y-1) #上
        elif action == 1:  new_head = (head_x, head_y+1) #下
        elif action == 2:  new_head = (head_x-1, head_y) #左
        elif action == 3:  new_head = (head_x+1, head_y) #右
        
        # 初始化奖励
        reward = 0
        done = False
        truncated = False
        
        # 碰撞检测（边界）
        if (new_head[0] < 0 or new_head[0] >= self.grid_size or 
            new_head[1] < 0 or new_head[1] >= self.grid_size):
            reward = -20  # 撞墙惩罚
            done = True
            return self._get_obs(), reward, done, truncated, {}
        
        # 碰撞检测（自身）
        if new_head in self.snake_body[:-1]:
            reward = -20  # 撞自己惩罚
            done = True
            return self._get_obs(), reward, done, truncated, {}
        
        # 计算距离奖励（更平滑的版本）
        if self.food_pos is not None:
            old_dist = np.sqrt((self.snake_body[0][0]-self.food_pos[0])**2 + 
                    (self.snake_body[0][1]-self.food_pos[1])**2)
            new_dist = np.sqrt((new_head[0]-self.food_pos[0])**2 + 
                    (new_head[1]-self.food_pos[1])**2)
            
            # 归一化距离奖励（基于网格大小）
            distance_reward = (old_dist - new_dist) / (self.grid_size * np.sqrt(2)) * 5
        else:
            distance_reward = 0
        
        # 插入新蛇头位置
        self.snake_body.insert(0, new_head)
        
        # 食物处理
        ate_food = False
        if self.food_pos is not None and new_head == self.food_pos:
            reward += 10  # 吃到食物的基础奖励
            ate_food = True
            self.food_pos = self._generate_food()
            
            # 长度奖励（鼓励增长）
            length_reward = len(self.snake_body) * 0.5
            reward += length_reward
        else:
            self.snake_body.pop()
        
        # 生存奖励（每步小惩罚，鼓励效率）
        survival_penalty = -0.1
        reward += survival_penalty
        
        # 总奖励组合
        reward += distance_reward
        
        # 检查胜利条件（吃到所有食物）
        if self.food_pos is None:
            reward += 50  # 完成游戏的额外奖励
            done = True
        
        # 步数限制
        self.steps += 1
        truncated = self.steps >= self.max_steps
        done = done or truncated
        
        # 如果吃到食物但游戏未结束，给予额外鼓励
        if ate_food and not done:
            reward += 2
        
        return self._get_obs(), reward, done, truncated, {}

    def render(self):
        if self.render_mode is None:
            return
        
        if self.fig is None:
            self.fig, self.ax = plt.subplots(figsize=(6,6))
            self.ax.set_xticks(np.arange(self.grid_size+1))
            self.ax.set_yticks(np.arange(self.grid_size+1))
            self.ax.grid(True, linestyle='-', linewidth=2)
            self.ax.set_xticklabels([])
            self.ax.set_yticklabels([])
            self.ax.invert_yaxis()
        
        # 清空画布
        for patch in self.ax.patches[:]:
            patch.remove()
        
        # 绘制网格线
        for i in range(self.grid_size+1):
            self.ax.axhline(i, color='black', linewidth=2)
            self.ax.axvline(i, color='black', linewidth=2)
        
        # 绘制食物
        if self.food_pos is not None:
            food = patches.Rectangle(
                (self.food_pos[1], self.food_pos[0]), 1, 1,
                facecolor='green', edgecolor='black', alpha=0.7
            )
            self.ax.add_patch(food)
        
        # 绘制蛇身
        for i, pos in enumerate(self.snake_body):
            color = 'red' if i == 0 else 'pink'
            body = patches.Rectangle(
                (pos[1], pos[0]), 1, 1,
                facecolor=color, edgecolor='black', alpha=0.7
            )
            self.ax.add_patch(body)
        
        # 更新显示
        plt.title(f"Steps: {self.steps}")
        plt.pause(0.1)

        filename = f"render_step_{self.steps}.png"
        self.fig.savefig(filename)

        if self.render_mode == 'rgb_array':
            self.fig.canvas.draw()
            img = np.frombuffer(self.fig.canvas.tostring_rgb(), dtype=np.uint8)
            return img.reshape(self.fig.canvas.get_width_height()[::-1] + (3,))


    



# 使用示例
if __name__ == "__main__":
    env = SnakeEnv(render_mode='human')
    obs, _ = env.reset()
    
    for _ in range(20):
        action = env.action_space.sample()
        obs, reward, done, truncated, info = env.step(action)
        print(obs.shape)
        print(f"{action} opposite: {env._get_opposite(action)}"  )
        env.render()
        
        if done or truncated:
            break
            
    env.close()