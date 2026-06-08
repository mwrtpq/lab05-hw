#include <gtest/gtest.h>
#include "Account.h"

TEST(Account, Constructor)
{
    Account account(1, 100);

    EXPECT_EQ(account.id(), 1);
    EXPECT_EQ(account.GetBalance(), 100);
}

TEST(Account, LockUnlock)
{
    Account account(1, 100);

    account.Lock();
    account.Unlock();

    SUCCEED();
}

TEST(Account, ChangeBalance)
{
    Account account(1, 100);

    account.Lock();
    account.ChangeBalance(50);

    EXPECT_EQ(account.GetBalance(), 150);

    account.Unlock();
}

TEST(Account, ChangeBalanceWithoutLock)
{
    Account account(1, 100);

    EXPECT_ANY_THROW(account.ChangeBalance(50));
}

