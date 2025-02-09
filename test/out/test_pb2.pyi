from google.protobuf.internal import containers as _containers
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Iterable as _Iterable, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class Hello(_message.Message):
    __slots__ = ("name",)
    NAME_FIELD_NUMBER: _ClassVar[int]
    name: str
    def __init__(self, name: _Optional[str] = ...) -> None: ...

class PackageIndex(_message.Message):
    __slots__ = ("Index",)
    INDEX_FIELD_NUMBER: _ClassVar[int]
    Index: int
    def __init__(self, Index: _Optional[int] = ...) -> None: ...

class PackageInfo(_message.Message):
    __slots__ = ("uid", "IntArr", "discription", "status")
    UID_FIELD_NUMBER: _ClassVar[int]
    INTARR_FIELD_NUMBER: _ClassVar[int]
    DISCRIPTION_FIELD_NUMBER: _ClassVar[int]
    STATUS_FIELD_NUMBER: _ClassVar[int]
    uid: int
    IntArr: _containers.RepeatedScalarFieldContainer[int]
    discription: str
    status: bool
    def __init__(self, uid: _Optional[int] = ..., IntArr: _Optional[_Iterable[int]] = ..., discription: _Optional[str] = ..., status: bool = ...) -> None: ...

class ClientInfo(_message.Message):
    __slots__ = ("Info",)
    INFO_FIELD_NUMBER: _ClassVar[int]
    Info: str
    def __init__(self, Info: _Optional[str] = ...) -> None: ...
