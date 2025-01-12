#pragma once
#include <iostream>
// [Play]
// [메뉴]
// (1)계좌개설, (2)입금, (3)출금 (4)전체 고객 잔액 조회 (Q) 종료
// (1)개설 -> (1)일반 (2)신용 (3)기부 -> [메뉴]에서 다시 선택
// (2)입금 후 -> 잔액 출력 -> [메뉴]에서 다시 선택
// (3)출금 후 -> 잔액 출력 -> [메뉴]에서 다시 선택
// (4)잔액 조회 후 -> [메뉴]에서 다시 선택
// (Q)종료 -> Menu에서 false return -> Play - if(Menu) return 0; 

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