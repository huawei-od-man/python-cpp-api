# 设置 CMake 最低版本要求
cmake_minimum_required(VERSION 3.16)

# 设置项目名称和版本
project(Python VERSION 1.0 LANGUAGES CXX)
option(BUILD_TEST "Whether to build test" ON)

if (BUILD_TEST)
    include(FetchContent)

    FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG release-1.12.1  # 使用最新的稳定版本
    )

    # 对于Windows用户，防止覆盖预编译的Windows运行时库
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    FetchContent_MakeAvailable(googletest)
endif()


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_library(Python
    "bool.cpp"
    box.cpp
    dict.cpp
    except.cpp
    floating_point.cpp
    "function.cpp"
    hash.cpp
    int.cpp
    "list.cpp"
    none.cpp
    object.cpp
    ref.cpp
    "set.cpp"
    str.cpp
    tuple.cpp
    "type.cpp"
    utils.cpp
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

if (BUILD_TEST)
    enable_testing()
    add_executable(tests
        bool_test.cpp
        str_test.cpp
        none_test.cpp
        floating_point_test.cpp
    )
    target_link_libraries(tests PRIVATE gtest_main Python)
    include(GoogleTest)
    gtest_discover_tests(
        tests
        EXTRA_ARGS --gtest_output=xml:${CMAKE_BINARY_DIR}/test_results/
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
