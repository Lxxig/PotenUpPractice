#pragma once
#include <iostream>
// [Play]
// [�޴�]
// (1)���°���, (2)�Ա�, (3)��� (4)��ü �� �ܾ� ��ȸ (Q) ����
// (1)���� -> (1)�Ϲ� (2)�ſ� (3)��� -> [�޴�]���� �ٽ� ����
// (2)�Ա� �� -> �ܾ� ��� -> [�޴�]���� �ٽ� ����
// (3)��� �� -> �ܾ� ��� -> [�޴�]���� �ٽ� ����
// (4)�ܾ� ��ȸ �� -> [�޴�]���� �ٽ� ����
// (Q)���� -> Menu���� false return -> Play - if(Menu) return 0; 

enum class EMenu
{
	CreateAccount = 1,
	Deposit = 2,
	Withdraw = 3,
	Inquire = 4,
};

struct Account;

class Bank
{
public:
	void Play();
	bool Menu();

	void CreateAccount();
	void CreateGeneralAccount();
	void CreateCreidtAccount();
	void CreateDonationAccount();
	bool Check() const;
	void Deposit();
	void Withdraw();
	int IdCheck(int inputId);
	void Inquire();

	~Bank();

private:
	Account* account[100];
	int AccountCnt = -1;

};