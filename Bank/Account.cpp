#include "Account.h"
#include <iostream>

Account::~Account()
{
	if (name != nullptr)
	{
		delete[] name;
		name = nullptr;
	}
}

Account::Account(const Account& other)
{
	id = other.id;
	balanced = other.balanced;

	size_t lenth = strlen(other.name);
	this->name = new char[lenth + 1];
	strcpy_s(this->name, lenth+1, other.name);
}