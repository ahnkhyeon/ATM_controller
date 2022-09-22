#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
using namespace std;

enum { DEPOSIT=1, WITHDRAW, BALANCE, EXIT };

class Account
{
private:
	string account;
	int balance;
	string cName;
public:
	Account(string ID, int money, string name);
	Account(const Account& ref);
	
	string Getaccount() const;
	int Getbalance() const;
	string Getcname() const;
	void Deposit(int money);
	int Withdraw(int money);
	void ShowAccInfo() const;
    ~Account();
};

#endif
