#include "account_handler.h"

void AccountHandler::ShowMenu(void) const
{
	cout << "------Menu------" << endl;
	cout << "1. Deposit" << endl;
	cout << "2. Withdraw" << endl;
	cout << "3. Show my account" << endl;
	cout << "4. Program Exit" << endl;
}

int AccountHandler::MakeAccount(const string& card_number)
{
	ifstream in("database.txt");
	string s;
	int balance;
	string name;

	int pos = 0;
	
	if(!in.is_open()) {
		cout << "cannot access server. Please contact the bank" << endl;
		return -1;
	}

	while(in) {
		in.clear();
		getline(in, s);
		if(*s.begin() == '[') {
			name = s.erase(0, 1);
			name = s.erase(s.size()-1, 1);
			continue;
		}
		pos = s.find(card_number, 0);
		if( pos != string::npos ) {
			int found = 0;
			int pos_t = 0;
			while(true) {
				pos_t = s.find(":", pos_t);
				if(pos_t > 0) {
					found++;
				}

				if(found == 2) {
					break;
				}
				pos_t++;
			}
			string s_balance = s.substr(pos_t+1, s.size()-pos_t);
			balance = atoi(s_balance.c_str());
			break;
		}
	}

	cout << "account_id:" << card_number << " balance: " << balance << " name : " << name << endl;

	accVec.push_back(new Account(card_number, balance, name));

	accTotal++;
	in.close();
	return 0;
}

void AccountHandler::DepositMoney(const string& id)
{
	int money;
	cout << "##Deposit##" << endl;
	cout << "Account ID: " << id << endl;
	cout << "Money: "; cin >> money;

	for (int i = 0; i < accTotal; i++)
	{
		if (accVec[i]->Getaccount() == id)
		{
			accVec[i]->Deposit(money);
			cout << "Complete" << endl << endl;
			return;
		}
	}
	cout << "Cannot find the account" << endl << endl;
}

void AccountHandler::WithdrawMoney(const string& id)
{
	int money;
	cout << "##Withdraw##" << endl;
	cout << "Account ID: " << id << endl;
	cout << "Money: "; cin >> money;

	for (int i = 0; i < accTotal; i++)
	{
		if (accVec[i]->Getaccount() == id)
		{
			if (accVec[i]->Withdraw(money) == 0)
			{
				cout << "Balance is not enough" << endl << endl;
				return;
			}

			cout << "Complete" << endl << endl;
			return;
		}
	}
	cout << "Cannot find the account" << endl << endl;
}

void AccountHandler::ShowAllAccInfo(void) const
{
	for (int i = 0; i < accTotal; i++)
	{
		accVec[i]->ShowAccInfo();
		cout << endl;
	}
}

void AccountHandler::UpdateDB(const vector<pair<string, string>>& account_data)
{
	
	ifstream in("database.txt", ios::binary);
	string backup_data;
	string name;

	if(in.is_open()){
		string temp;
		while(in) {
			temp = "";
			getline(in, temp);
			if(temp[0] == '['){
				name = temp;
				name += '\n';
				continue;
			}
			int pos = temp.find(account_data[0].first);
			if( pos == string::npos){
				backup_data += temp;
				backup_data += '\n';
			}
		}
	}
//	cout << "backup_data" << backup_data << "END" << endl;

	in.close();

	ofstream out("database.txt" , ios::ate);
	string s;
	for(int i = 0; i < accTotal; i++)
	{
		if(accVec[i]->Getaccount() == account_data[0].first)
		{
			s = account_data[0].first + ":" + account_data[0].second + ":" + to_string(accVec[i]->Getbalance());
			s += '\n';
		}
	}
	if(out.is_open()){
		out << name;
		out << s;
		out << backup_data;
	}
	out.close();

}

AccountHandler::AccountHandler()
	:accTotal(0)
{}
AccountHandler::~AccountHandler()
{
	for (int i = 0; i < accTotal; i++)
		delete accVec[i];
}
