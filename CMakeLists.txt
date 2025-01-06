cmake_minimum_required(VERSION 3.10)

# 设置项目名称
project(card_game)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(${PROJECT_SOURCE_DIR})

# 添加可执行文件
add_executable(card_game
    main.cpp
    game.cpp
    player.cpp
)