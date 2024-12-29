#pragma once
#include <iostream>

enum class AccountType
{
	GeneralAccount = 1,
	CreditAccount = 2,
	DonationAccount = 3
};

struct Account
{
	Account();
	Account(AccountType accountType);

	Account(const Account& other);
	
	virtual ~Account();

	int id = 0;
	char* name = nullptr;
	float balanced = 0;
	AccountType accountType = AccountType::GeneralAccount;
};

struct CreditAccount : public Account
{
	CreditAccount();
	float interestRate = 0.01f;
};

struct DonationAccount : public Account
{
	DonationAccount();
	float donationRate = 0.01f;
	float donationAmount = 0.0f;
};