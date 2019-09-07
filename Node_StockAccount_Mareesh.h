
//This file defines a node for the doubly linked list defined by class StockAccount
#ifndef NODE_STOCKACCOUNT_MAREESH_H
#define NODE_STOCKACCOUNT_MAREESH_H


#include <string>

using namespace std;

class Node {
	friend class StockAccount;
	friend class SortImpl;
	friend class SortSelection;
	friend class SortBubble;

public:
	//default constructor
	Node(string name, int no, double pps)
		:stock_symbol(name), num_of_shares(no), price_per_share(pps)
	{
		this->pre = NULL;
		this->next = NULL;
	}

private:
	string stock_symbol;
	int num_of_shares;
	double price_per_share;
	Node *next;
	Node *pre;
};

#endif