#ifndef __ACCOUNT_HANDLER_H_
#define __ACCOUNT_HANDLER_H_

#include "account.h"

class AccountHandler
{
private:
	vector<Account*> accVec;
	int accTotal;
public:
	AccountHandler();
	void ShowMenu(void) const;
	int MakeAccount(const string&);
	void DepositMoney(const string&);
	void WithdrawMoney(const string&);
	void ShowAllAccInfo(void) const;
	void UpdateDB(const vector<pair<string, string>>&);
	~AccountHandler();
};

#endif
