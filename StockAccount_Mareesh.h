
//class StockAccount handles stock portfolio by using doubly linked list
#ifndef STOCKACCOUNT__MAREESH_H
#define	STOCKACCOUNT__MAREESH_H

#include "Account_Mareesh.h"
#include "Node_StockAccount_Mareesh.h"
#include "Sorting_Implementation_Mareesh.h"

//Class StockAccount- to handle all the stock account related operations

class StockAccount : public Account{
public:
	StockAccount();
	~StockAccount();
	//design pattern- template
	//3. Derived classes implement placeholder methods
	virtual string getName() const
	{
		return "Stock Portfolio Account";
	}
	int size() const;
	double get_stock_price(string, string);
	void print_portfolio();
	void update_list(string);
	void buy_shares(string, string, int, double);
	void sell_shares(string, string, int, double);
	void store_portfolio();
	void get_trans_history();
	void get_graph();
private:
	Node *Head;
	int mySize;	//stores the number of nodes in doubly linked list
	SortImpl *impl;
};

#endif