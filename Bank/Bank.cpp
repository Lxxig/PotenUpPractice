#include "Bank.h"
#include <iostream>
#include "Account.h"

void Bank::Play()
{
	while (true)
	{
		if (Menu() == false) return;
	}
}

bool Bank::Menu()
{
	while (true)
	{
		char input;
		std::cout << "\n===========================================================\n";
		std::cout << "(1)계좌 개설 (2)입금 (3)출금 (4)전체 고객 잔액 조회 (Q) 종료\n";
		std::cout << "===========================================================\n>> ";
		std::cin >> input;
		if (input == 'Q') return false;

		switch (static_cast<EMenu>(input - '0'))
		{
		case EMenu::CreateAccount:
			CreateAccount(); break;
		case EMenu::Deposit:
			if (AccountCnt < 0) continue;  // 계좌가 하나도 존재하지 않으면 continue
			Deposit(); break;
		case EMenu::Withdraw:
			if (AccountCnt < 0) continue;
			Withdraw(); break;
		case EMenu::Inquire:
			if (AccountCnt < 0) continue;
			Inquire(); break;
		default:
			break;
		}
	}
}

void Bank::CreateAccount()
{
	AccountCnt++;
	account[AccountCnt] = new Account();
	while (true)
	{
		char name[100];
		std::cout << "\n===========================================================\n";
		std::cout << "			[계좌 개설]\n";
		std::cout << "===========================================================\n";
		std::cout << "ID(ID > 0) & Name(100자 이내)\n>> ";
		std::cin >> account[AccountCnt]->id >> name;
		size_t nameSize = strlen(name) + 1;
		account[AccountCnt]->name = new char[nameSize];
		strcpy_s(account[AccountCnt]->name, nameSize, name);

		// 계좌 번호 중복 체크
		if (Check()) continue;
		else
		{
			std::cout << "\n계좌 개설 완료!\n";
			break;
		}
	}
}

bool Bank::Check() const
{
	for (int i = 0; i < AccountCnt; ++i)
	{
		if (account[AccountCnt]->id == account[i]->id) return true;
	}
	return false;
}

void Bank::Deposit()
{
	while (true)
	{
		int inputID, depositMoney;
		std::cout << "\n===========================================================\n";
		std::cout << "			[입금]\n";
		std::cout << "===========================================================\n";
		std::cout << "ID(계좌 번호): ";
		std::cin >> inputID;

		// 존재하는지 체크하고 존재하면 아이디에 해당하는 
		// 인덱스 반환, 없으면 -1 반환
		int idIndex = IdCheck(inputID);
		if (idIndex == -1)
		{
			std::cout << "\n계좌번호를 다시 입력해주세요.\n";
			continue;
		}
		else
		{
			std::cout << "\n입금할 금액: ";
			std::cin >> depositMoney;
			account[idIndex]->balanced += depositMoney;
			std::cout << "잔액: " << account[idIndex]->balanced << std::endl;
			break;
		}
	}

	return;
}

void Bank::Withdraw()
{
	while (true)
	{
		int inputID, depositMoney;
		std::cout << "\n===========================================================\n";
		std::cout << "			[출금]\n";
		std::cout << "===========================================================\n";
		std::cout << "ID(계좌 번호): ";
		std::cin >> inputID;

		// 존재하는지 체크하고 존재하면 아이디에 해당하는 
		// 인덱스 반환, 없으면 -1 반환
		int idIndex = IdCheck(inputID);
		if (idIndex == -1)
		{
			std::cout << "\n계좌번호를 다시 입력해주세요.\n";
			continue;
		}
		else
		{
			std::cout << "잔액: " << account[idIndex]->balanced;
			std::cout << "\n출금할 금액: ";
			std::cin >> depositMoney;
			account[idIndex]->balanced -= depositMoney;

			// 잔액 보다 더 많이 출금하는 것을 막기
			if (account[idIndex]->balanced < 0)
			{
				account[idIndex]->balanced += depositMoney;
				std::cout << "잔액이 부족합니다.\n"; continue;
			}
			std::cout << "잔액: " << account[idIndex]->balanced << std::endl;
			break;
		}
	}

	return;
}

int Bank::IdCheck(int inputID)
{
	for (int i = 0; i <= AccountCnt; ++i)
	{
		if (account[i]->id == inputID) return i;
	}
	return -1;
}

void Bank::Inquire()
{
	std::cout << "\n===========================================================\n";
	std::cout << "		[전체 고객 잔액 조회]\n";
	std::cout << "===========================================================\n";
	for (int i = 0; i <= AccountCnt; ++i)
	{
		std::cout << "Name:	" << account[i]->name << "	ID:	" << account[i]->id << "	Balanced:	" << account[i]->balanced << std::endl;
	}
}

Bank::~Bank()
{
	for (int i = 0; i <= AccountCnt; ++i)
	{
		if (account[i] != nullptr)
		{
			delete account[i];
			account[i] = nullptr;
		}
	}
}
