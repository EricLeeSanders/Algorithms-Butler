//Eric Sanders

#include <time.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <vector>
using namespace std;


/*
Represents an item that has an id, profit, weight, and ratio
*/
class Item
{
public:
	int id, profit, weight;

	void setValues(int _id, int _profit, int _weight) {
		id = _id;
		profit = _profit;
		weight = _weight;
	}
};

int max(int p, int q) {
	if (p < q) {
		return q;
	}
	else {
		return p;
	}
}

int knapsack_simple(int **sol, vector<Item> items, int capacity) {
	//initialize table with 0's
	for(int i = 0; i < items.size(); i++) {
		for(int j = 0; j < capacity; j++) {
			sol[i][j] = 0;
		}
	}
	for (int i = 1; i <= items.size(); i++) {
		for(int w = 1; w <= capacity; w++) {
			//Only do the following if the weight of the item is less than or equal to w(current capacity)
			if(items[i-1].weight <= w) {
				sol[i][w] = max(items[i-1].profit + sol[i - 1][w - items[i-1].weight]
					, sol[i - 1][w]);
			}
			else {
				sol[i][w] = sol[i - 1][w];
			}
		}
	}
	return sol[items.size()][capacity];
}
vector<Item> add_items(int **sol, vector<Item> items, int capacity ) {
	vector<Item> items_in_solution;
	int i = items.size(), w = capacity;
	while(i > 0) {
		//if they aren't equal then, we know that it changed at i.
		if(sol[i][w] != sol[i-1][w]) {
			items_in_solution.push_back(items[i-1]); //get the item
			w = w - items[i-1].weight;
		}
		i--;
	}

	return items_in_solution;
}
int main() {
	int num_items, capacity;
	string input;
	cout << "Knapsack Dynamic Simple" << endl;
	cout << "What is the filename?: ";
	cin >> input;
	ifstream filein(input.c_str());
	filein >> num_items >> capacity;
	

	vector<Item> items;
	int item_id;
	int profit;
	int weight;

	int **sol = new int *[num_items + 1];
	for (int i = 0; i <= num_items; i++) {

		sol[i] = new int[capacity + 1];
	}
	for (int i = 0; i < num_items; i++) {
		filein >> item_id >> profit >> weight;
		Item item;
		item.setValues(item_id, profit, weight);
		items.push_back(item);
	}
	int answer = knapsack_simple(sol, items, capacity);

	//Print table
	/*	for(int i = 1; i <= num_items; i++) {
		cout << "Row " << i << " ";
		for(int j = 1; j <= capacity; j++) {
			cout << "Column " << j << ": ";
			cout << P[i][j] << endl;
		}
	}
	*/
	int totalWeight = 0;
	vector<Item> items_in_solution = add_items(sol, items, capacity);
	for(int i = 0; i < items_in_solution.size(); i++) {
		cout << items_in_solution[i].id << " " << items_in_solution[i].profit << " " << items_in_solution[i].weight << endl;
		totalWeight = totalWeight + items_in_solution[i].weight;
	}
	
	cout <<"Simple Total Value: " << answer << endl;
	cout << "Simple Total Weight: " << totalWeight << endl;


	for (int i = 0; i <= num_items; i++) {
		delete[] sol[i];
	}
	delete [] sol;

	int pause;
	cin >> pause;

	return 0;
}
