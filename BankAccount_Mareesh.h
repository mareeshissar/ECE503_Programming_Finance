
#ifndef BANKACCOUNT__MAREESH_H
#define	BANKACCOUNT__MAREESH_H

#include "Account_Mareesh.h"

//Class BankAccount- to handle all the bank account related operations

class BankAccount : public Account {

public:
	//design pattern- template
	//3. Derived classes implement placeholder methods
	virtual string getName() const
	{
		return "Bank Account";
	}
	void withdraw(double);
	void deposit(double);
	void get_trans_history() const;
};

#endif

