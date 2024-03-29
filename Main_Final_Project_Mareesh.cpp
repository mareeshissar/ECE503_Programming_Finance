// Name: Mareesh Kumar Issar
// Date of submission: Dec 17, 2018
// Course: 16:332:503, Programming Finance
// Program name: Account Management System


#include <iostream>
#include <string>
#include <time.h>
#include <iomanip>

#include "StockAccount_Mareesh.h"
#include "BankAccount_Mareesh.h"

using namespace std;

string  getFileName();	//function for randomly selecting a file

int main()						//start of main()- program execution begins
{
	BankAccount bank_account;			//instantiate object of class BankAccount
	StockAccount stock_account;			//instantiate object of class StockAccount
	
	//for implementing the design pattern- template
	Account *array[] = {&stock_account,  &bank_account};

	//displaying name of the program to the user
	cout << "WELCOME TO THE ACCOUNT MANAGEMENT SYSTEM." << endl << endl;

	//variable for capturing response of the user
	int option;
	int choice = 0;
	int choice1 = 0;
	int choice2 = 0;
	int num_of_shares;
	double amt, sp, max_amt_per_share, min_amt_per_share;
	string stock_symbol;

	while (choice !=3)			
	{
			cout << "Please select an account to access:" << endl;
			cout << "1: Stock Portfolio Account " << endl;
			cout << "2: Bank Account" << endl;
			cout << "3: Exit " << endl;

			cout << endl << "Enter your choice: ";
			cin >> choice;

			switch (choice)
			{
			case 1://stock portfolio account
				while (choice1 != 7)
				{
					cout << endl;
					//for implementing the design pattern- template
					array[0]->print_type();
					cout << "1: Display the price for a stock symbol " << endl;
					cout << "2: Display the current portfolio" << endl;
					cout << "3: Buy shares" << endl;
					cout << "4: Sell shares" << endl;
					cout << "5: View a graph for the portfolio value" << endl;
					cout << "6: View transaction history" << endl;
					cout << "7: Return to previous menu " << endl;
					cout << "Please select an option:" << endl;;
					cin >> option;

					switch (option)
					{
					case 1://displaying price for a stock symbol
						cout << endl << "Please enter the stock symbol: ";
						cin >> stock_symbol;
						sp = stock_account.get_stock_price(getFileName(), stock_symbol);
						if (sp != -1)
						{
							cout << "Company Symbol     " << "Price per share" << endl;
							cout << stock_symbol << setw(18) << "$" << sp << '\n';
						}
						else
							cout << "Symbol not found!!!" << endl;
						break;

					case 2://displaying current portfolio
						stock_account.print_portfolio();
						break;

					case 3://buy shares
						cout << endl << "Please enter the stock symbol you want to purchase: ";
						cin >> stock_symbol;
						cout << endl << "Please enter the number of shares: ";
						cin >> num_of_shares;
						cout << endl << "Please enter the maximum amount you are willing to pay per share: ";
						cin >> max_amt_per_share;
						stock_account.buy_shares(getFileName(), stock_symbol, num_of_shares, max_amt_per_share);
						break;

					case 4://sell shares
						cout << endl << "Please enter the stock symbol you want to sell: ";
						cin >> stock_symbol;
						cout << endl << "Please enter the number of shares: ";
						cin >> num_of_shares;
						cout << endl << "Please enter the minimum amount you are willing to pay per share: ";
						cin >> min_amt_per_share;
						stock_account.sell_shares(getFileName(), stock_symbol, num_of_shares, min_amt_per_share);
						break;

					case 5://view graph for portfolio value
						stock_account.get_graph();
						break;

					case 6://view transaction history
						stock_account.get_trans_history();
						break;

					case 7://return to previous menu
						choice1 = 7;
						cout << endl << endl;
						break;

					default:
						cout << "You have entered wrong choice" << endl << endl;
						break;
					}
				}
				choice1 = 0;
			break;

			case 2://bank account
				while (choice2 != 5)
				{
					cout << endl;
					//for implementing the design pattern- template
					array[1]->print_type();
					cout << "1: View account balance " << endl;
					cout << "2: Deposit money" << endl;
					cout << "3: Withdraw money" << endl;
					cout << "4: Print out history" << endl;
					cout << "5: Return to previous menu " << endl;
					cout << "Please select an option:" << endl;
					cin >> option;
					cout << endl;

					switch (option)
					{
					case 1://view account balance
						cout << "You have $" << bank_account.get_cash_balance() << " in your bank account" << endl;
						break;

					case 2://deposit money
						cout << "Please enter the amount: ";
						cin >> amt;
						bank_account.deposit(amt);
						break;

					case 3://withdraw money
						cout << "Please enter the amount: ";
						cin >> amt;
						bank_account.withdraw(amt);
						break;

					case 4://print transaction history
						bank_account.get_trans_history();
						break;

					case 5://return to previous menu
						choice2 = 5;
						cout << endl << endl;
						break;

					default:
						cout << "You have entered wrong choice" << endl << endl;
						break;
					}
				}
				choice2 = 0;
			break;

			case 3://exit
				cout << endl << "Thank you, have a nice day!" << endl;
				choice = 3;
				break;

			default:
				cout << endl << "You have entered wrong choice" << endl << endl;
				break;
			}
	}
	//to store the total portfolio value and stock portfolio
	stock_account.store_portfolio();
	return 0; //indicates successful termination
}			  // end of main 


string getFileName()
{
	int x;
	string file[2] = { "Result_1.txt","Result_2.txt" };

	srand(time(0));							//for seeding rand() with the current time in seconds
	x = rand() % 2;							//generating random number(x) from 0-1

	return file[x];
}

