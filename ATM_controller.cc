#include "account_handler.h"

void CheckDatabase(vector<pair<string, string>>* account_data, const string card_string, bool* fail_flag, mutex* m, condition_variable* cv) {
	ifstream in("database.txt");
	string buf;
	int pos = 0;

	
	if(!in.is_open()) {
		cout << "cannot access server. Please contact the bank" << endl;
		return;
	}
	
	this_thread::sleep_for(chrono::milliseconds(500));
	m->lock();
	while(in) {
		getline(in, buf);
		if(buf[0] == '[') continue;
		pos = 0;
		pos = string(buf).find(":", pos);
		string card_number = string(buf).substr(0, 19);
		string pin_number = string(buf).substr(pos+1, 4);
		if(card_number == card_string){
			account_data->push_back(make_pair(card_number, pin_number));
			in.close();
			cv->notify_one();
			m->unlock();
			return;
		}	
	}
	*fail_flag = true;
	in.close();
	cv->notify_one();
	m->unlock();
	return;
}

void CheckPinNumber(vector<pair<string, string>>* account_data, bool *fail_flag, bool *pin_flag, mutex* m, condition_variable* cv) {

	string pin_number;
	int failure = 0, PIN_NUMBER_SIZE = 4;

	unique_lock<mutex> lk(*m);

	cout << "Please wait for a moment..." << endl;

	cv->wait(lk, [&](){ return !account_data->empty() ||  *fail_flag == true; });

	if(!account_data->empty())
		cout << "Succeed to checking card number." << endl;
	else{
		cout << "Card number may be wrong. Please try again." << endl;
		return;
	}
	
	while(1) {	
		
		if(failure >= 5) {
			cout << "You cannot access the account (Attempts over)" << endl;
			return;
		}

		cout << "Please enter your pin number: ";
		cin >> pin_number;
		if( (pin_number.size() != 4) || ((*account_data)[0].second != pin_number) ) {
			failure++;
			cout << "Pin number length is 4. Please try to enter your PIN again " << "( " << failure << " / " << " 5 )" <<endl;
		}else{
			cout << "Succeed to check PIN number" << endl;
			*pin_flag = true;
			return;
		}
	}
}


int main(void)
{
	AccountHandler manager;
	int choice = 0;
	vector<pair<string, string>> account_data;
	mutex m;
	condition_variable cv;
	string card_number = "";
	bool fail_flag = false, pin_flag = false;

	cout << "Welcome to Bear Bank!!!" << endl;
	

	while (1)
	{
		cout << "Please insert the card number(XXXX-XXXX-XXXX-XXXX)" << endl;
		cin >> card_number;

		thread traverseDB(CheckDatabase, &account_data, card_number, &fail_flag, &m, &cv);
		thread checkPIN(CheckPinNumber, &account_data, &fail_flag, &pin_flag, &m, &cv);
		traverseDB.join();
		checkPIN.join();

		if(account_data.empty()) continue;

		if(!pin_flag || manager.MakeAccount(card_number) < 0) {
			cout << "Please insert card again" << endl;
			account_data.resize(0);
			fail_flag = false;
			pin_flag = false;
			card_number = "";	
			continue;
		}
		break;
	}
		
	while(1){
		manager.ShowMenu();
		cout << "Choice: ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
			case DEPOSIT:
				manager.DepositMoney(card_number);
				break;
			case WITHDRAW:
				manager.WithdrawMoney(card_number);
				break;
			case BALANCE:
				manager.ShowAllAccInfo();
				break;
			case EXIT:
				manager.UpdateDB(account_data);
				return 0;
			default:
				cout << "Illegal selection..." << endl;
		}
		
	}

	return 0;
}
