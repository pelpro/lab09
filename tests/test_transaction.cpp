#include "Transaction.h"
#include "Account.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using::testing::AtLeast;
using::testing::DoAll;
using::testing::Return;

class MockAccount: public Account {
public:
	MockAccount(int id, int sum) : Account(id, sum) {}
        MOCK_METHOD0(id, int());
	MOCK_METHOD0(GetBalance, int());
	MOCK_METHOD1(ChangeBalance, void(int diff));
	MOCK_METHOD0(Lock, void());
	MOCK_METHOD0(Unlock, void());
};

TEST(Transaction, TransactionMock)
{
        MockAccount first(1, 1000), second(2, 1000);
        Transaction transaction;

        EXPECT_CALL(first, Lock())
                .Times(1);
        EXPECT_CALL(second, Lock())
                .Times(1);
        EXPECT_CALL(second, ChangeBalance(100))
                .Times(1);
        EXPECT_CALL(first, ChangeBalance(-100))
                .Times(1);
        EXPECT_CALL(firsy, Unlock())
                .Times(1);
        EXPECT_CALL(second, Unlock())
                .Times(1);

        transaction.Make(first, second, 100);
}

TEST(Transaction, TransactionInvalid)
{
        MockAccount first(1, 1000), second(2, 1000);
        Transaction transaction;
        EXPECT_THROW(transaction.Make(first, first, 150), std::logic_error);
}

TEST(Transaction, TransactionNegative)
{
        MockAccount first(1, 1000), second(2, 1000);
        Transaction transaction;
        EXPECT_THROW(transaction.Make(first, second, -1), std::invalid_argument);
}

TEST(Transaction, TransactionSmall)
{
        MockAccount first(1, 1000), second(2, 1000);
        Transaction transaction;
        EXPECT_THROW(transaction.Make(first, second, 10), std::logic_error);
}

TEST(Transaction, TransactionEnough)
{
        Account first(1, 1000), second(2, 1000);
        Transaction transaction;
        transaction.Make(first, second, 100);
        EXPECT_EQ(first.GetBalance(), 900);
        EXPECT_EQ(second.GetBalance(), 1100);
}

TEST(Transaction, TransactionNotEnoughFunds)
{
        Account first(1, 1000), second(2, 1000);
        Transaction transaction;
        transaction.Make(first, second, 1500);

	EXPECT_EQ(first.GetBalance(), 1000);
        EXPECT_EQ(second
		  .GetBalance(), 1000);

}

