from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class Hello(_message.Message):
    __slots__ = ("msg",)
    MSG_FIELD_NUMBER: _ClassVar[int]
    msg: str
    def __init__(self, msg: _Optional[str] = ...) -> None: ...

class GameData(_message.Message):
    __slots__ = ("game_over", "snake", "foods", "map", "score")
    GAME_OVER_FIELD_NUMBER: _ClassVar[int]
    SNAKE_FIELD_NUMBER: _ClassVar[int]
    FOODS_FIELD_NUMBER: _ClassVar[int]
    MAP_FIELD_NUMBER: _ClassVar[int]
    SCORE_FIELD_NUMBER: _ClassVar[int]
    game_over: bool
    snake: Snake
    foods: _containers.RepeatedCompositeFieldContainer[Food]
    map: Map
    score: int
    def __init__(self, game_over: bool = ..., snake: _Optional[_Union[Snake, _Mapping]] = ..., foods: _Optional[_Iterable[_Union[Food, _Mapping]]] = ..., map: _Optional[_Union[Map, _Mapping]] = ..., score: _Optional[int] = ...) -> None: ...

class Snake(_message.Message):
    __slots__ = ("body",)
    BODY_FIELD_NUMBER: _ClassVar[int]
    body: _containers.RepeatedCompositeFieldContainer[Position]
    def __init__(self, body: _Optional[_Iterable[_Union[Position, _Mapping]]] = ...) -> None: ...

class Food(_message.Message):
    __slots__ = ("position",)
    POSITION_FIELD_NUMBER: _ClassVar[int]
    position: Position
    def __init__(self, position: _Optional[_Union[Position, _Mapping]] = ...) -> None: ...

class Map(_message.Message):
    __slots__ = ("width", "height", "walls")
    WIDTH_FIELD_NUMBER: _ClassVar[int]
    HEIGHT_FIELD_NUMBER: _ClassVar[int]
    WALLS_FIELD_NUMBER: _ClassVar[int]
    width: int
    height: int
    walls: _containers.RepeatedCompositeFieldContainer[Position]
    def __init__(self, width: _Optional[int] = ..., height: _Optional[int] = ..., walls: _Optional[_Iterable[_Union[Position, _Mapping]]] = ...) -> None: ...

class Position(_message.Message):
    __slots__ = ("x", "y")
    X_FIELD_NUMBER: _ClassVar[int]
    Y_FIELD_NUMBER: _ClassVar[int]
    x: int
    y: int
    def __init__(self, x: _Optional[int] = ..., y: _Optional[int] = ...) -> None: ...

class operation(_message.Message):
    __slots__ = ("direction",)
    DIRECTION_FIELD_NUMBER: _ClassVar[int]
    direction: str
    def __init__(self, direction: _Optional[str] = ...) -> None: ...
