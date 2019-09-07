
//for implementing design pattern- strategy
#ifndef SORTING_IMPLEMENTATION_MAREESH_H
#define SORTING_IMPLEMENTATION_MAREESH_H


#include <iostream>
#include <string>

using namespace std;

class SortImpl {
public:
	//pure virtual function
	virtual Node* sort(Node *) = 0;

};

class SortSelection : public SortImpl {
public:
	virtual Node* sort(Node *Start)
	{
		Node *current_ptr = Start;
		Node *largest_ptr = Start;
		string temp_ss;
		int temp_sh;
		double temp_pps;

		do
		{
			current_ptr = largest_ptr->next;

			while (current_ptr != NULL)
			{
				if ((current_ptr->num_of_shares*current_ptr->price_per_share) > (largest_ptr->num_of_shares*largest_ptr->price_per_share))
				{
					//swapping
					temp_ss = largest_ptr->stock_symbol;
					temp_sh = largest_ptr->num_of_shares;
					temp_pps = largest_ptr->price_per_share;

					largest_ptr->stock_symbol = current_ptr->stock_symbol;
					largest_ptr->num_of_shares = current_ptr->num_of_shares;
					largest_ptr->price_per_share = current_ptr->price_per_share;

					current_ptr->stock_symbol = temp_ss;
					current_ptr->num_of_shares = temp_sh;
					current_ptr->price_per_share = temp_pps;

				}
				current_ptr = current_ptr->next;
			}
			largest_ptr = largest_ptr->next;
		} while (largest_ptr != NULL);
		return Start;
	}
};

class SortBubble : public SortImpl {
public:
	virtual Node* sort(Node *Start)
	{
		bool flag;
		Node *current_ptr = Start;
		Node *lastPtr = NULL;
		string temp_ss;
		int temp_sh;
		double temp_pps;

		do
		{
			flag = false;
			current_ptr = Start;

			while (current_ptr->next != lastPtr)
			{
				if ((current_ptr->num_of_shares*current_ptr->price_per_share) < (current_ptr->next->num_of_shares*current_ptr->next->price_per_share))
				{
					//swapping
					temp_ss = current_ptr->stock_symbol;
					temp_sh = current_ptr->num_of_shares;
					temp_pps = current_ptr->price_per_share;

					current_ptr->stock_symbol = current_ptr->next->stock_symbol;
					current_ptr->num_of_shares = current_ptr->next->num_of_shares;
					current_ptr->price_per_share = current_ptr->next->price_per_share;

					current_ptr->next->stock_symbol = temp_ss;
					current_ptr->next->num_of_shares = temp_sh;
					current_ptr->next->price_per_share = temp_pps;

					flag = true;
				}
				current_ptr = current_ptr->next;
			}
			lastPtr = current_ptr;

		} while (flag == true);	//for checking if elements were swapped in the inner while loop
		return Start;
	}
};



#endif