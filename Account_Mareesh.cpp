
#include"Account_Mareesh.h"

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

Account::Account()
{
	//bank_account_cash_balance.txt- has the value of cash_balance

	//if file is created for the first time
	ifstream file1("bank_account_cash_balance.txt");
	if (file1.is_open() == 0)
	{
		//set initial balance of $10000
		cash_balance = 10000.00;
		ofstream file2;
		file2.open("bank_account_cash_balance.txt");
		file2 << setprecision(2) << fixed;
		file2 << cash_balance << endl;
		file2.close();
		file1.close();
	}

	//if file is already present 
	else
	{
		double readValue;
		ifstream file1("bank_account_cash_balance.txt");
		file1 >> readValue;
		cash_balance = readValue;
		file1.close();
	}

}

void Account::set_cash_balance(double b)
{
	ofstream file2;
	//replaces the value present in the file with b
	file2.open("bank_account_cash_balance.txt");
	file2 << b << endl;
	file2.close();
}

double Account::get_cash_balance() const
{
	string l;
	ifstream file1("bank_account_cash_balance.txt");
	if (file1.is_open())
	{
		while (getline(file1, l))
		{
			return stod(l);		//stod converts string to double
		}

		file1.close();
	}

	else
	{
		cout << "Error in opening file" << endl;
	}

	return -1;
}