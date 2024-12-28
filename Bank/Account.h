#pragma once
#include <iostream>

struct Account
{
	~Account()
	{
		if (name != nullptr)
		{
			delete[] name;
			name = nullptr;
		}
	}

	int id = 0;
	char* name = nullptr;
	int balanced = 0;
};