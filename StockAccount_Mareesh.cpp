

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#include <stdio.h>

#include <yvals.h>
#if (_MSC_VER >= 1600)
#define __STDC_UTF_16__
#endif

#include "mex.h"
#include <engine.h>
#include <vector>

#pragma comment(lib, "libmx.lib")
#pragma comment(lib, "libmex.lib")
#pragma comment(lib, "libeng.lib")


using namespace std;

#include "StockAccount_Mareesh.h"
#include "BankAccount_Mareesh.h"

//default constructor
StockAccount::StockAccount()
	:Head(0)
{
	mySize = 0;
	
	//for implementing design pattern- strategy
	impl = new SortSelection;

	//stock_portfolio.txt- has information about the latest stock portfolio

	//if file is created for the first time
	ifstream file("stock_portfolio.txt");
	if (file.is_open() == 0)
	{
		file.close();
	}

	//if the file already has some stocks then create a DLL with all the values
	else
	{
		int count = 0;
		string l, stock_symbol;
		int num_of_shares;
		double price_per_share;
		Node *current_ptr = NULL;

		if (file.is_open())
		{
			while (file>>l)
			{
				stock_symbol = l;
				file >> l;
				num_of_shares = stoi(l);   //stod converts string to integer
				file >> l;
				price_per_share = stod(l);

				//create a new dll node
				Node *new_node = new Node(stock_symbol, num_of_shares, price_per_share);

				//if it is the first node in the list
				if (count == 0)
				{
					Head = new_node;
					current_ptr = Head;
					count++;
					mySize++;
				}
				
				//insert the new_node at the end of the list
				else
				{
					current_ptr->next = new_node;
					new_node->pre = current_ptr;
					current_ptr = current_ptr->next;
					mySize++;
				}
				
			}

			file.close();
		}
	}
}

//destructor
StockAccount::~StockAccount()
{
	//if stock portfolio list is not empty
	if (size() != 0)			
	{
		Node *current_ptr = Head;
		Node *temp_ptr;

		while (current_ptr != 0)
		{
			temp_ptr = current_ptr;
			current_ptr = current_ptr->next;
			delete temp_ptr;
		}
	}
}

//member function for returning size of the list
int StockAccount::size() const
{
	return mySize;
}

//member function for getting price for a stock symbol
double StockAccount::get_stock_price(string fileName, string stock_symbol)
{
	string l;

	//fileName has the name of a randomly generated file- to mimick stock price fluctuations

	ifstream file1(fileName);
	if (file1.is_open())
	{
		while (file1 >> l)
		{
			if (l == stock_symbol)
			{
				file1 >> l;
				return stod(l);			//stod converts string to double
			}

		}

		file1.close();
	}

	else
	{
		cout << "Error in opening file" << endl;
	}
	
	//if symbol not found
	return -1;
}

//member function for displaying the current portfolio
void StockAccount::print_portfolio()
{
	double total = 0.0;

	//if list is empty, no stock in stock portfolio
	if (size() == 0)
	{
		cout << endl << "Cash balance= $" << get_cash_balance() << endl << endl;
		cout << "The stock portfolio is empty" << endl;
		cout << "Total portfolio value= $" << get_cash_balance() << endl;
		return;
	}

	else
	{
		Node *current_ptr = Head;
		cout << endl << "Cash balance= $" << get_cash_balance() << endl << endl;
		cout << left << setw(18) << "Company Symbol" << left << setw(11) << "Number" << left << setw(19) << "Price per share" << "Total value" << endl;


		while (current_ptr != 0)
		{
			cout << setprecision(2) << fixed;
			cout << left << setw(18) << current_ptr->stock_symbol << left << setw(11) << current_ptr->num_of_shares << left << setw(1) << "$" << left << setw(18) << current_ptr->price_per_share << left << setw(1) << "$" << current_ptr->num_of_shares*current_ptr->price_per_share << endl;
			total += current_ptr->num_of_shares*current_ptr->price_per_share;
			current_ptr = current_ptr->next;
		}
		cout << "Total portfolio value= $" << get_cash_balance() + total << endl;
	}
}

//member function for updating the list according to most recent price per share 
void StockAccount::update_list(string fileName)
{
	Node *current_ptr = Head;

	//fileName contains the most recent stock price for all the stocks

	while (current_ptr != 0)
	{
		current_ptr->price_per_share = get_stock_price(fileName, current_ptr->stock_symbol);
		current_ptr = current_ptr->next;
	}

}

//member function for buying shares
void StockAccount::buy_shares(string fileName, string stock_symbol, int num_of_shares, double max_amt_per_share)
{
	double curr_amt_per_share;
	int choice, count = 0;

	if (num_of_shares*max_amt_per_share > get_cash_balance())
	{
		cout << "Transaction failed due to insufficient cash balance in bank account" << endl << endl;
	}

	else
	{
		curr_amt_per_share = get_stock_price(fileName, stock_symbol);

		//if stock symbol is not present
		if (curr_amt_per_share == -1)
			cout << "Symbol not found!!!" << endl << endl;

		else
		{
			if (curr_amt_per_share > max_amt_per_share)
			{
				cout << "Transaction failed because price per share is higher than the maximum amount you are willing to pay" << endl << endl;
			}

			else
			{
				//create new dll node
				Node *new_node = new Node(stock_symbol, num_of_shares, curr_amt_per_share);

				//check if list is empty
				if (size() == 0)
				{
					//new_node becomes the head
					Head = new_node;
					mySize++;

					BankAccount *b= new BankAccount();
					b->withdraw(num_of_shares*curr_amt_per_share);
					delete b;
					set_cash_balance( get_cash_balance()-(num_of_shares*curr_amt_per_share) );

					cout << "You have purchased " << num_of_shares << " shares of " << stock_symbol << " at $" << curr_amt_per_share << " each for a total of $" << num_of_shares * curr_amt_per_share << endl;

					ofstream file2;
					file2.open("stock_transaction_history.txt", ios::app);
					time_t seconds;
					seconds = time(NULL);
					char time[9];
					tm *timeinfo;
					timeinfo = localtime(&seconds);
					strftime(time, 100, "%X", timeinfo);
					file2 << setprecision(2) << fixed;
					file2 << left << setw(10) << "Buy" << left << setw(16) << stock_symbol << left << setw(8) << num_of_shares << left << left << setw(1) << "$" << setw(19) << curr_amt_per_share << left << setw(1) << "$" << left << setw(15) << num_of_shares * curr_amt_per_share << time << endl;
					file2.close();

				}

				//if list is not empty
				else
				{
					//check if that stock is already present
					Node *current_ptr = Head;
					while (current_ptr != NULL)
					{
						if (current_ptr->stock_symbol == new_node->stock_symbol)
						{
							current_ptr->num_of_shares += new_node->num_of_shares;
							count = 1;	//indicator variable

							BankAccount *b = new BankAccount();
							b->withdraw(num_of_shares*curr_amt_per_share);
							delete b;

							set_cash_balance(get_cash_balance() - (num_of_shares*curr_amt_per_share));

							cout << "You have purchased " << num_of_shares << " shares of " << stock_symbol << " at $" << curr_amt_per_share << " each for a total of $" << num_of_shares * curr_amt_per_share << endl;

							ofstream file2;
							file2.open("stock_transaction_history.txt", ios::app);
							time_t seconds;
							seconds = time(NULL);
							char time[9];
							tm *timeinfo;
							timeinfo = localtime(&seconds);
							strftime(time, 100, "%X", timeinfo);
							file2 << setprecision(2) << fixed;
							file2 << left << setw(10) << "Buy" << left << setw(16) << stock_symbol << left << setw(8) << num_of_shares << left << left << setw(1) << "$" << setw(19) << curr_amt_per_share << left << setw(1) << "$" << left << setw(15) << num_of_shares * curr_amt_per_share << time << endl;
							file2.close();

							
						}

						current_ptr = current_ptr->next;
					}


					//if stock not already present
					if (count == 0)
					{
						Node *current_ptr = Head;

						//inserting at the end
						while (current_ptr->next != NULL)
							current_ptr = current_ptr->next;

						current_ptr->next = new_node;
						new_node->pre = current_ptr;
						mySize++;

						BankAccount *b = new BankAccount();
						b->withdraw(num_of_shares*curr_amt_per_share);
						delete b;

						set_cash_balance(get_cash_balance() - (num_of_shares*curr_amt_per_share));

						cout << "You have purchased " << num_of_shares << " shares of " << stock_symbol << " at $" << curr_amt_per_share << " each for a total of $" << num_of_shares * curr_amt_per_share << endl;

						ofstream file2;
						file2.open("stock_transaction_history.txt", ios::app);
						time_t seconds;
						seconds = time(NULL);
						char time[9];
						tm *timeinfo;
						timeinfo = localtime(&seconds);
						strftime(time, 100, "%X", timeinfo);
						file2 << setprecision(2) << fixed;
						file2 << left << setw(10) << "Buy" << left << setw(16) << stock_symbol << left << setw(8) << num_of_shares << left << left << setw(1) << "$" << setw(19) << curr_amt_per_share << left << setw(1) << "$" << left << setw(15) << num_of_shares * curr_amt_per_share << time << endl;
						file2.close();

					
					}
				}
			}
		}
	}

	//updating the recent price per share for all the stocks in the list
	update_list(fileName);

	//for implementing design pattern- strategy
	if (size() > 1)
	{
		cout << endl << "Select the sorting algorithm that you would like to use" << endl;
		cout << "1: Selection sort" << endl;
		cout << "2: Bubble sort" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://selection sort
			delete impl;
			impl = new SortSelection;
			Head=impl->sort(Head);
			break;

		case 2://bubble sort
			delete impl;
			impl = new SortBubble;
			Head=impl->sort(Head);
			break;

		default:cout << "You have entered wrong choice" << endl;
			break;
		}
	}
	print_portfolio();
	store_portfolio();	
}

//member function for selling shares
void StockAccount::sell_shares(string fileName, string stock_symbol, int num_of_shares, double min_amt_per_share)
{
	double curr_amt_per_share;
	int choice, count = 0;

	curr_amt_per_share = get_stock_price(fileName, stock_symbol);
	Node *current_ptr = Head;
	Node *temp = NULL;

	if (size() == 0)
		cout << "The stock portfolio is empty" << endl;

	else
	{
		while (current_ptr != NULL)
		{
			if (current_ptr->stock_symbol == stock_symbol)
			{
				if (num_of_shares > current_ptr->num_of_shares)
				{
					cout << "Transaction failed due of insufficient number of shares" << endl;
				}

				else
				{
					if (current_ptr->price_per_share < min_amt_per_share)
						cout << "Transaction failed because the price per share is less than the amount you are willing to sell" << endl;

					else
					{
						current_ptr->num_of_shares -= num_of_shares;

						//check if the stock needs to be removed from the list
						if (current_ptr->num_of_shares == 0)
						{
							temp = current_ptr;

							//if head needs to be removed
							if (Head == current_ptr)
								Head = current_ptr->next;

							//if node to be removed is not the last node
							if (current_ptr->next != NULL)
								current_ptr->next->pre = current_ptr->pre;

							//if node to be removed is not the first node
							if (current_ptr->pre != NULL)
								current_ptr->pre->next = current_ptr->next;

							mySize--;
						}

						BankAccount *b = new BankAccount();
						b->deposit(num_of_shares*curr_amt_per_share);
						delete b;

						set_cash_balance(get_cash_balance() + (num_of_shares*curr_amt_per_share));

						cout << "You have sold " << num_of_shares << " shares of " << stock_symbol << " at $" << curr_amt_per_share << " each for a total of $" << num_of_shares * curr_amt_per_share << endl;

						ofstream file2;
						file2.open("stock_transaction_history.txt", ios::app);
						time_t seconds;
						seconds = time(NULL);
						char time[9];
						tm *timeinfo;
						timeinfo = localtime(&seconds);
						strftime(time, 100, "%X", timeinfo);
						file2 << setprecision(2) << fixed;
						file2 << left << setw(10) << "Sell" << left << setw(16) << stock_symbol << left << setw(8) << num_of_shares << left << left << setw(1) << "$" << setw(19) << curr_amt_per_share << left << setw(1) << "$" << left << setw(15) << num_of_shares * curr_amt_per_share << time << endl;
						file2.close();
					}
				}
				count = 1;//indicator variable
			}
			current_ptr = current_ptr->next;
		}

		if (count == 0)
			cout << "Symbol not found!!!" << endl;
	}

	//updating the recent price per share for all the stocks in the list
	update_list(fileName);

	//for implementing design pattern- strategy
	if (size() > 1 && count != 0)
	{
		cout << endl << "Select the sorting algorithm that you would like to use" << endl;
		cout << "1: Selection sort" << endl;
		cout << "2: Bubble sort" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1://selection sort
			delete impl;
			impl = new SortSelection;
			Head=impl->sort(Head);
			break;
		case 2://bubble sort
			delete impl;
			impl = new SortBubble;
			Head=impl->sort(Head);
			break;

		default:cout << "You have entered wrong choice" << endl;
			break;
		}
	}
	print_portfolio();
	store_portfolio();

	//deleting the node to be removed
	delete temp;
}

//member function for getting the transaction history
void StockAccount::get_trans_history()
{
	string l;
	ifstream file1("stock_transaction_history.txt");
	cout << left << setw(10) << "Event" << left << setw(16) << "Company Symbol" << left << setw(8) << "Number" << left << setw(20) << "Price per share" << left << setw(16) << "Total value" << "Time" << endl;
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


//member function for getting graph
void StockAccount::get_graph()
{
	Engine *ep;
	ep = engOpen(NULL);
	if (ep == NULL) {
		cout << "Error: Not Found" << endl;
		exit(1);
	}

	vector<double> value;
	vector<double> time;

	double *value_array = new double;
	double *time_array = new double;

	string l;
	int counter1 = 1, counter2 = 1;

	ifstream file1("total_portfolio_value.txt");
	if (file1.is_open())
	{
		while (file1 >> l)
		{
			//for reading total portfolio value
			if ((counter1 - 1) % 3 == 0)
			{
				value.push_back(stod(l));
			}

			//for reading time in seconds
			if ((counter2 + 1) % 3 == 0)
			{
				time.push_back(stod(l));
			}

			counter1++;
			counter2++;
		}

		file1.close();
	}

	else
	{
		cout << "Error in opening file";
	}

	for (int i = 0; i < value.size(); i++)
	{
		value_array[i] = value[i];
		time_array[i] = time[i] - time[0];
	}

	mxArray *A;
	A = mxCreateDoubleMatrix(1, value.size(), mxREAL);
	memcpy((void *)mxGetPr(A), (void *)value_array, sizeof(double) * value.size());

	mxArray *B;
	B = mxCreateDoubleMatrix(1, time.size(), mxREAL);
	memcpy((void *)mxGetPr(B), (void *)time_array, sizeof(double) * time.size());

	engPutVariable(ep, "Time", B);
	engPutVariable(ep, "Portfolio_value", A);
	engEvalString(ep, "plot(Time, Portfolio_value)");
	engEvalString(ep, "title('Total portfolio value Vs Time')");
	engEvalString(ep, "xlabel('Time(seconds)')");
	engEvalString(ep, "ylabel('Total portfolio value')");


	system("pause");

	//clean operation
	mxDestroyArray(B);
	mxDestroyArray(A);
	engEvalString(ep, "close;");

	//close engine
	engClose(ep);
	return;
}

//member function for storing the portfolio and total portfolio value
void StockAccount::store_portfolio()
{
	double total = 0.0;

	Node *current_ptr = Head;
	
	//if list is empty
	if (size()==0)
	{
		//delete the stock_portfolio.txt file
		remove("stock_portfolio.txt");
	}

	else
	{
		//delete the stock_portfolio.txt file
		remove("stock_portfolio.txt");

		while (current_ptr != 0)
		{
			total += current_ptr->num_of_shares*current_ptr->price_per_share;

			//write to stock_portfolio.txt file
			ofstream file2;
			file2.open("stock_portfolio.txt", ios::app);
			file2 << setprecision(2) << fixed;
			file2 << left << setw(10) << current_ptr->stock_symbol << left << setw(10) << current_ptr->num_of_shares << left << setw(16) << current_ptr->price_per_share << endl;
			file2.close();

			current_ptr = current_ptr->next;
		}

	}

		
	//for storing the total portfolio value
	ofstream file2;
	file2.open("total_portfolio_value.txt", ios::app);
	time_t seconds;
	seconds = time(NULL);
	char date[9];
	tm *timeinfo;
	timeinfo = localtime(&seconds);
	strftime(date, 100, "%D", timeinfo);
	file2 << setprecision(2) << fixed;
	file2 << left << setw(16) << get_cash_balance() + total << left << setw(16) << seconds << date << endl;
	file2.close();
}

