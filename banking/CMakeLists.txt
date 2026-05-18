cmake_minimum_required(VERSION 3.4)

project(banking)

set(CMAKE_CXX_STANDARD 11)

add_library(banking

    Account.cpp

    Transaction.cpp

)

target_include_directories(banking PUBLIC

    ${CMAKE_CURRENT_SOURCE_DIR}

)

add_subdirectory(third-party/gtest)

enable_testing()

add_executable(check
    tests/account_test.cpp
    tests/transaction_test.cpp
)

target_link_libraries(check
    banking
    gtest_main
)

add_test(NAME check COMMAND check)
