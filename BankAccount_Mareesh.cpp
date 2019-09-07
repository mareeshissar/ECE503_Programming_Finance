
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <time.h>
#include <string>

using namespace std;

#include "BankAccount_Mareesh.h"

//member function for withdrawing money
void BankAccount::withdraw(double amt)
{
	if (amt>get_cash_balance())
		cout << "Transaction failed due to insufficient cash balance in bank account" << endl;
	
	else
	{
		set_cash_balance(get_cash_balance() - amt);
		cout << "You have successfully withdrawn $" << amt << " from your bank account" << endl;

		//write to bank_transaction_history.txt file
		ofstream file2;
		file2.open("bank_transaction_history.txt", ios::app);
		time_t seconds;
		seconds = time(NULL);
		char date[9];
		tm *timeinfo;
		timeinfo = localtime(&seconds);
		strftime(date, 100, "%D", timeinfo);
		file2 << setprecision(2) << fixed;
		file2 << left << setw(10) << "Withdraw" << left << setw(1) << "$" << setw(11) << amt << left << setw(10) << date << left<< setw(1) << "$" << left << setw(19) << get_cash_balance() << endl;
		file2.close();

		
	}
}

//member function for depositing money
void BankAccount::deposit(double amt)
{
	set_cash_balance(get_cash_balance() + amt);
	cout << "You have successfully deposited $" << amt << " to your bank account" << endl;

	//write to bank_transaction_history.txt file
	ofstream file2;
	file2.open("bank_transaction_history.txt", ios::app);
	time_t seconds;
	seconds = time(NULL);
	char date[9];
	tm *timeinfo;
	timeinfo = localtime(&seconds);
	strftime(date, 100, "%D", timeinfo);
	file2 << setprecision(2) << fixed;
	file2 << left << setw(10) << "Deposit" << left << setw(1) << "$" << setw(11) << amt << left << setw(10) << date << left << setw(1) << "$" << left << setw(19) << get_cash_balance() << endl;
	file2.close();

	
}

//member function for printing transaction history
void BankAccount::get_trans_history() const
{
	string l;
	
	//bank_transaction_history.txt- has all the bank transaction history 

	ifstream file1("bank_transaction_history.txt");
	cout << left << setw(10) << "Event" << left << setw(12) << "Amount" << left << setw(10) << "Date" << left << setw(20) << "Balance" << endl;
	if (file1.is_open())
	{
		while (getline(file1, l))
		{
			cout << l << endl;
		}

		file1.close();
	}

	else
	{
		cout << "Error in opening file" << endl;
	}
}