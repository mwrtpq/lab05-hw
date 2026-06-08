#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Account.h"
#include "Transaction.h"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

class MockAccount : public Account
{
public:
    MockAccount(int id, int balance) : Account(id, balance) {}

    MOCK_METHOD(int, GetBalance, (), (const, override));
    MOCK_METHOD(void, ChangeBalance, (int diff), (override));
    MOCK_METHOD(void, Lock, (), (override));
    MOCK_METHOD(void, Unlock, (), (override));
};

TEST(Transaction, SuccessfulTransfer)
{
    NiceMock<MockAccount> from(1, 1000);
    NiceMock<MockAccount> to(2, 500);

    Transaction transaction;
    transaction.set_fee(10);

    EXPECT_CALL(from, GetBalance())
        .WillRepeatedly(Return(1000));

    EXPECT_CALL(to, GetBalance())
        .WillRepeatedly(Return(500));

    EXPECT_CALL(from, ChangeBalance(-110))
        .Times(1);

    EXPECT_CALL(to, ChangeBalance(100))
        .Times(1);

    EXPECT_TRUE(transaction.Make(from, to, 100));
}

TEST(Transaction, SameAccount)
{
    NiceMock<MockAccount> account(1, 1000);

    Transaction transaction;

    EXPECT_THROW(
        transaction.Make(account, account, 100),
        std::logic_error
    );
}

TEST(Transaction, NegativeSum)
{
    NiceMock<MockAccount> from(1, 1000);
    NiceMock<MockAccount> to(2, 500);

    Transaction transaction;

    EXPECT_THROW(
        transaction.Make(from, to, -100),
        std::invalid_argument
    );
}

TEST(Transaction, TooSmallSum)
{
    NiceMock<MockAccount> from(1, 1000);
    NiceMock<MockAccount> to(2, 500);

    Transaction transaction;

    EXPECT_THROW(
        transaction.Make(from, to, 0),
        std::logic_error
    );
}

TEST(Transaction, NotEnoughMoney)
{
    NiceMock<MockAccount> from(1, 50);
    NiceMock<MockAccount> to(2, 500);

    Transaction transaction;
    transaction.set_fee(10);

    EXPECT_CALL(from, GetBalance())
        .WillRepeatedly(Return(50));

    EXPECT_CALL(to, GetBalance())
        .WillRepeatedly(Return(500));

    EXPECT_FALSE(transaction.Make(from, to, 100));
}
