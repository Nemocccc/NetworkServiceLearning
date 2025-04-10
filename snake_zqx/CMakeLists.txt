cmake_minimum_required(VERSION 3.10)

project(Snake)

# 指定 C++ 编译器
set(CMAKE_CXX_COMPILER "D:/w64devkit/bin/g++.exe")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含源文件目录
aux_source_directory(. DIR_SRCS)
aux_source_directory(${CMAKE_SOURCE_DIR}/tcp DIR_SRCS)

# 添加可执行文件
add_executable(Snake ${DIR_SRCS})

# 链接 ws2_32 库
target_link_libraries(Snake ws2_32)

# 设置安装路径
install(TARGETS Snake DESTINATION bin)

# 构建一个 CPack 驱动的安装包
include(InstallRequiredSystemLibraries)
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_NAME "Snake")
set(CPACK_PACKAGE_CONTACT "Nemo 1774747097@qq.com")
include(CPack)