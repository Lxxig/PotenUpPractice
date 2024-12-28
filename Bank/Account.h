#pragma once
#include <iostream>

struct Account
{
	~Account();

	Account(const Account& other);

	int id = 0;
	char* name = nullptr;
	int balanced = 0;
};