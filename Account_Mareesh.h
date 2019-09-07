
#ifndef ACCOUNT_MAREESH_H
#define	ACCOUNT_MAREESH_H


#include<iostream>
#include<string>

using namespace std;

//Abstract base class- Account

class Account {

private:
	double cash_balance;

public:
	Account();

	//pure virtual function
	//2. Steps requiring peculiar implementations are "placeholders" in base class
	virtual string getName() const = 0;

	/*   
		 implementing the design pattern- template
	     1. This function standardizes the skeleton of an algorithm in a base class "template method"
	*/
	void print_type()
	{
		cout << getName() << endl;
	}

	void set_cash_balance(double);
	double get_cash_balance() const;
};


#endif