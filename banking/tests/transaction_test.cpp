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
