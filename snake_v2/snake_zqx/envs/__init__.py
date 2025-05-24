from gymnasium.envs.registration import register

register(
    id = 'Snake-v0',
    entry_point = 'envs.Snake_v0:SnakeEnv'
)

register(
    id = 'Snake-v1',
    entry_point = 'envs.Snake_v1:SnakeEnv'
)