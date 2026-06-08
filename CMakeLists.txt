cmake_minimum_required(VERSION 3.4)

project(lab05)

set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_library(banking
    banking/Account.cpp
    banking/Transaction.cpp
)

target_include_directories(banking PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/banking
)

add_subdirectory(third-party/gtest)

add_executable(check
    tests/account_test.cpp
    tests/transaction_test.cpp
)

target_link_libraries(check
    banking
    gtest_main
    gmock
)

add_test(NAME check COMMAND check)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
