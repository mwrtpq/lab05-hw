```bash
cat > CMakeLists.txt <<EOF
cmake_minimum_required(VERSION 3.4)

project(banking)

set(CMAKE_CXX_STANDARD 11)

add_library(banking
    Account.cpp
    Transaction.cpp
)

target_include_directories(banking PUBLIC
    \${CMAKE_CURRENT_SOURCE_DIR}
)
EOF
```

```bash
mkdir -p third-party
git submodule add https://github.com/google/googletest third-party/gtest
```

```bash
mkdir -p tests

cat > tests/account_test.cpp <<EOF
#include <gtest/gtest.h>
#include "Account.h"

TEST(Account, Constructor)
{
    Account account(1, 100);
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(Account, ChangeBalance)
{
    Account account(1, 100);
    account.Lock();
    account.ChangeBalance(50);
    EXPECT_EQ(account.GetBalance(), 150);
    account.Unlock();
}
EOF

cat > tests/transaction_test.cpp <<EOF
#include <gtest/gtest.h>
#include "Account.h"
#include "Transaction.h"

TEST(Transaction, Transfer)
{
    Account from(1, 1000);
    Account to(2, 500);

    Transaction transaction;
    transaction.set_fee(10);

    EXPECT_TRUE(transaction.Make(from, to, 100));
    EXPECT_EQ(from.GetBalance(), 890);
    EXPECT_EQ(to.GetBalance(), 600);
}
EOF
```

```bash
cat >> CMakeLists.txt <<EOF

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
EOF
```

```bash
git add .
git commit -m "added"
git push origin main
```
