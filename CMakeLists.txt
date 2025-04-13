# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(Python VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 添加库目标
aux_source_directory(${CMAKE_SOURCE_DIR} SOURCES)

add_library(Python
    ${SOURCES}
)

# 设置库的头文件路径
target_include_directories(Python PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# 安装规则（可选）
install(TARGETS Python
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

add_executable(main main.cpp)

target_link_libraries(main Python)
