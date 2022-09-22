#include "account.h"

Account::Account(string ID, int money, string name) : account(ID), balance(money), cName(name) {}

Account::Account(const Account& ref) : account(ref.account), balance(ref.balance), cName(ref.cName) {}

string Account::Getaccount() const
{
	return account;
}

int Account::Getbalance() const 
{
	return balance;
}

string Account::Getcname() const
{
	return cName;
}

void Account::Deposit(int money)
{
	balance += money;
}

int Account::Withdraw(int money)
{
	if (balance < money)
		return 0;

	balance -= money;
	return money;
}

void Account::ShowAccInfo() const
{
	cout << "Account ID: " << account << endl;
	cout << "Name: " << cName << endl;
	cout << "Balance: " << balance << endl;
}

Account::~Account() {}
