from envs import *
from envs.Snake_v0 import *

def decode(response):
        '''将c++中传输过来的数据解包'''
        #print(f"Received response: {response}")
            
        # 取出 game_over 的值
        terminated = response['game_over']
        print("game_over:", terminated)

        # 取出 snake 的值，snake 是一个包含多个字典的列表
        snake = response['snake']
        snake_body = []
        for segment in snake:
            snake_body.append(tuple(segment.values()))
        print(snake_body)

        # 取出 foods 的值，foods 是一个包含多个字典的列表
        foods = response['foods']
        all_food_pos = []
        
        for segment in foods:
            all_food_pos.append(tuple(segment.values()))
        print(all_food_pos)

        # 取出 map 的值，map 是一个字典
        game_map = response['map']
        width = game_map['width']
        height = game_map['height']
        walls = game_map['walls']

        # print("Map width:", width)
        # print("Map height:", height)
        # print("Walls:", walls)

        all_walls_pos = []
        for segment in walls:
            all_walls_pos.append(tuple(segment.values()))
        #print(all_walls_pos)
        # 取出 score 的值
        score = response['score']
        print("score:", score)

        steps = 0

        #游戏是否中断 c++中应该返回 若不返回可以直接设为false
        truncated = False

        #无用信息 不用管
        _ = {}
        return all_food_pos,snake_body, all_walls_pos,steps, score, terminated, truncated,_


def obs_interface(all_food_pos, snake_body, all_wall_pos):
    '''将解包后的数据转换为状态'''
    obs_grid = np.zeros((GridSize,GridSize), dtype=int)
    # 标记食物
    if len(all_food_pos) >0:
        for food_pos in all_food_pos: 
            obs_grid[food_pos[0]//2,food_pos[1]] = 2

    # 标记蛇身
    for i, pos in enumerate(snake_body):
        # i== 0 时为蛇头
        obs_grid[pos[0]//2,pos[1]] = 3 if i == 0 else 1
    
    
    if len(all_wall_pos) >0:
        for wall_pos in all_wall_pos:
            # obs_grid[wall_pos[0], wall_pos[1]] = 4 
            pass
    
    return obs_grid.flatten()
    

def action_interface(action:int):
    # 0
    '''将动作转换为要发送的指令'''
    directions = ['up', 'down', 'left', 'right']
    
    command = directions[action]

    return command


def obs_trans(env,obs_grid):
    "将obs_gird.flaaten()转换为envs的food_pos,snake_body"
    obs_grid = obs_grid.reshape((GridSize, GridSize))
    env.snake_body = []
    env.food_pos = []
    for i in range(GridSize):
        for j in range(GridSize):
            if obs_grid[i, j] == 3:
                env.snake_body.append((i, j))
            elif obs_grid[i, j] == 2:
                env.food_pos.append((i, j))
            elif obs_grid[i, j] == 1:
                env.snake_body.append((i, j))
                
