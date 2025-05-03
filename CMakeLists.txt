# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.10)

# 设置项目名称和版本
project(Python VERSION 1.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加库目标
file(GLOB_RECURSE  SOURCES CONFIGURE_DEPENDS
    *.cpp
)

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
cmake_minimum_required(VERSION 3.16)

project(python-cpp-api)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1  # 使用最新的稳定版本
)

# 对于Windows用户，防止覆盖预编译的Windows运行时库
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

include_directories(src)

add_subdirectory(test)
