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
#include <gtest/gtest.h>

#include "Account.h"
#include "Transaction.h"

class MockTransaction : public Transaction
{
public:
    void SaveToDataBase(Account&, Account&, int) override
    {
        saved = true;
    }

    bool saved = false;
};

TEST(Transaction, SetFee)
{
    MockTransaction transaction;

    transaction.set_fee(10);

    EXPECT_EQ(transaction.fee(), 10);
}

TEST(Transaction, SuccessfulTransfer)
{
    Account from(1, 1000);
    Account to(2, 500);

    MockTransaction transaction;

    transaction.set_fee(10);

    EXPECT_TRUE(transaction.Make(from, to, 100));

    EXPECT_EQ(from.GetBalance(), 890);
    EXPECT_EQ(to.GetBalance(), 600);

    EXPECT_TRUE(transaction.saved);
}

TEST(Transaction, SameAccount)
{
    Account account(1, 1000);

    MockTransaction transaction;

    EXPECT_THROW(
        transaction.Make(account, account, 100),
        std::logic_error
    );
}

TEST(Transaction, NegativeSum)
{
    Account from(1, 1000);
    Account to(2, 500);

    MockTransaction transaction;

    EXPECT_THROW(
        transaction.Make(from, to, -100),
        std::logic_error
    );
}

TEST(Transaction, TooSmallSum)
{
    Account from(1, 1000);
    Account to(2, 500);

    MockTransaction transaction;

    EXPECT_THROW(
        transaction.Make(from, to, 0),
        std::logic_error
    );
}

TEST(Transaction, NotEnoughMoney)
{
    Account from(1, 50);
    Account to(2, 500);

    MockTransaction transaction;

    transaction.set_fee(10);

    EXPECT_FALSE(transaction.Make(from, to, 100));

    EXPECT_EQ(from.GetBalance(), 50);
    EXPECT_EQ(to.GetBalance(), 500);
}
