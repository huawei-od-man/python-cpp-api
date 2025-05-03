enable_testing()

add_executable(unittests
    test_ref.cpp
)

target_link_libraries(unittests
    PRIVATE
    gtest_main
)

add_test(NAME unittests COMMAND unittests)
