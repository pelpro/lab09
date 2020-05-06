#include "Account.h"

#include <gtest/gtest.h>

TEST(Account, AccountTestAll)
{
	Account first(1, 1000);
	
	EXPECT_EQ(first.id(), 1);
	EXPECT_EQ(first.GetBalance(), 1000);
	EXPECT_THROW(first.ChangeBalance(100), std::runtime_error);
	EXPECT_EQ(first.id(), 1);	
	EXPECT_EQ(first.GetBalance(), 1000);

	EXPECT_NO_THROW(first.Lock());
	EXPECT_THROW(first.Lock(), std::runtime_error);
	EXPECT_EQ(first.GetBalance(), 1000);
	EXPECT_NO_THROW(first.ChangeBalance(500));
	EXPECT_EQ(first.GetBalance(), 1500);

	EXPECT_EQ(first.id(), 1);

	EXPECT_NO_THROW(first.Unlock());
	EXPECT_NO_THROW(first.Unlock());
	EXPECT_EQ(first.id(), 1);
	EXPECT_EQ(first.GetBalance(), 1500);
	EXPECT_THROW(first.ChangeBalance(500), std::runtime_error);
}

