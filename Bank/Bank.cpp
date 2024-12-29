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
		std::cout << "(1)���� ���� (2)�Ա� (3)��� (4)��ü �� �ܾ� ��ȸ (Q) ����\n";
		std::cout << "===========================================================\n>> ";
		std::cin >> input;
		if (input == 'Q') return false;

		switch (static_cast<EMenu>(input - '0'))
		{
		case EMenu::CreateAccount:
			CreateAccount(); return true;
		case EMenu::Deposit:
			if (AccountCnt < 0) continue;  // ���°� �ϳ��� �������� ������ continue
			Deposit(); return true;
		case EMenu::Withdraw:
			if (AccountCnt < 0) continue;
			Withdraw(); return true;
		case EMenu::Inquire:
			if (AccountCnt < 0) continue;
			Inquire(); return true;
		default:
			break;
		}
	}
}

void Bank::CreateAccount()
{
	AccountCnt++;

	while (true)
	{
		int input;
		std::cout << "\n===========================================================\n";
		std::cout << "			[���� ����]\n";
		std::cout << "	(1)�Ϲ� ����, (2)�ſ� ���� (3)��� ����\n";
		std::cout << "===========================================================\n";
		std::cout << ">> ";
		std::cin >> input;
		switch (static_cast<AccountType>(input))
		{
		case AccountType::GeneralAccount:
			CreateGeneralAccount(); return;
		case AccountType::CreditAccount:
			CreateCreidtAccount(); return;
		case AccountType::DonationAccount:
			CreateDonationAccount(); return;
		default:
			continue;
		}
	}
}

void Bank::CreateGeneralAccount()
{
	account[AccountCnt] = new Account();
	while (true)
	{
		char name[100];
		std::cout << "\n===========================================================\n";
		std::cout << "			[�Ϲ� ���� ����]\n";
		std::cout << "===========================================================\n";
		std::cout << "ID(ID > 0) & Name(100�� �̳�)\n>> ";
		std::cin >> account[AccountCnt]->id >> name;
		size_t nameSize = strlen(name) + 1;
		account[AccountCnt]->name = new char[nameSize];
		strcpy_s(account[AccountCnt]->name, nameSize, name);

		// ���� ��ȣ �ߺ� üũ
		if (Check()) continue;
		else
		{
			std::cout << "\n���� ���� �Ϸ�!\n";
			break;
		}
	}
}

void Bank::CreateCreidtAccount()
{
	account[AccountCnt] = new CreditAccount();
	while (true)
	{
		char name[100];
		std::cout << "\n===========================================================\n";
		std::cout << "			[�ſ� ���� ����]\n";
		std::cout << "===========================================================\n";
		std::cout << "ID(ID > 0) & Name(100�� �̳�)\n>> ";
		std::cin >> account[AccountCnt]->id >> name;
		size_t nameSize = strlen(name) + 1;
		account[AccountCnt]->name = new char[nameSize];
		strcpy_s(account[AccountCnt]->name, nameSize, name);

		// ���� ��ȣ �ߺ� üũ
		if (Check()) continue;
		else
		{
			std::cout << "\n���� ���� �Ϸ�!\n";
			break;
		}
	}
}

void Bank::CreateDonationAccount()
{
	account[AccountCnt] = new DonationAccount();
	while (true)
	{
		char name[100];
		std::cout << "\n===========================================================\n";
		std::cout << "			[��� ���� ����]\n";
		std::cout << "===========================================================\n";
		std::cout << "ID(ID > 0) & Name(100�� �̳�)\n>> ";
		std::cin >> account[AccountCnt]->id >> name;
		size_t nameSize = strlen(name) + 1;
		account[AccountCnt]->name = new char[nameSize];
		strcpy_s(account[AccountCnt]->name, nameSize, name);

		// ���� ��ȣ �ߺ� üũ
		if (Check()) continue;
		else
		{
			std::cout << "\n���� ���� �Ϸ�!\n";
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
		std::cout << "			[�Ա�]\n";
		std::cout << "===========================================================\n";
		std::cout << "ID(���� ��ȣ): ";
		std::cin >> inputID;

		// �����ϴ��� üũ�ϰ� �����ϸ� ���̵� �ش��ϴ� 
		// �ε��� ��ȯ, ������ -1 ��ȯ
		int idIndex = IdCheck(inputID);
		if (idIndex == -1)
		{
			std::cout << "\n���¹�ȣ�� �ٽ� �Է����ּ���.\n";
			continue;
		}
		else
		{
			std::cout << "\n�Ա��� �ݾ�: ";
			std::cin >> depositMoney;
			account[idIndex]->balanced += depositMoney;
			if (account[idIndex]->accountType == AccountType::CreditAccount)
			{
				account[idIndex]->balanced += depositMoney * ((CreditAccount*)account[idIndex])->interestRate;
			}
			else if (account[idIndex]->accountType == AccountType::DonationAccount)
			{
				account[idIndex]->balanced -= depositMoney * ((DonationAccount*)account[idIndex])->donationRate;
				((DonationAccount*)account[idIndex])->donationAmount += depositMoney * ((DonationAccount*)account[idIndex])->donationRate;
			}
			std::cout << "�ܾ�: " << account[idIndex]->balanced << std::endl;
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
		std::cout << "\n=============================================================================\n";
		std::cout << "			[���]\n";
		std::cout << "=============================================================================\n";
		std::cout << "ID(���� ��ȣ): ";
		std::cin >> inputID;

		// �����ϴ��� üũ�ϰ� �����ϸ� ���̵� �ش��ϴ� 
		// �ε��� ��ȯ, ������ -1 ��ȯ
		int idIndex = IdCheck(inputID);
		if (idIndex == -1)
		{
			std::cout << "\n���¹�ȣ�� �ٽ� �Է����ּ���.\n";
			continue;
		}
		else
		{
			std::cout << "�ܾ�: " << account[idIndex]->balanced;
			std::cout << "\n����� �ݾ�: ";
			std::cin >> depositMoney;
			account[idIndex]->balanced -= depositMoney;

			// �ܾ� ���� �� ���� ����ϴ� ���� ����
			if (account[idIndex]->balanced < 0)
			{
				account[idIndex]->balanced += depositMoney;
				std::cout << "�ܾ��� �����մϴ�.\n"; continue;
			}
			std::cout << "�ܾ�: " << account[idIndex]->balanced << std::endl;
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
	std::cout << "\n=============================================================================================\n";
	std::cout << "		[��ü �� �ܾ� ��ȸ]\n";
	std::cout << "=============================================================================================\n";
	for (int i = 0; i <= AccountCnt; ++i)
	{
		//std::cout << "Name:	" << account[i]->name << "	ID:	" << account[i]->id << "	Balanced:	" << account[i]->balanced << std::endl;
		if (account[i]->accountType == AccountType::GeneralAccount)
		{
			std::cout << "[�Ϲ� ����] " << "Name:	" << account[i]->name << "	ID:	" << account[i]->id << "	Balanced:	" << account[i]->balanced << std::endl;
		}
		else if (account[i]->accountType == AccountType::CreditAccount)
		{
			std::cout << "[�ſ� ����] " << "Name:	" << account[i]->name << "	ID:	" << account[i]->id << "	Balanced:	" << account[i]->balanced << std::endl;
		}
		else
		{
			std::cout << "[��� ����] " << "Name:	" << account[i]->name << "	ID:	" << account[i]->id << "	Balanced:	" << account[i]->balanced << "	DonationAmount:	" << ((DonationAccount*)account[i])->donationAmount << std::endl;
		}
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
