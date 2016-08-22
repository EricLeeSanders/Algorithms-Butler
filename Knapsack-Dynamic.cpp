//Eric Sanders
//Algorithms
//Project - Entrapment
//Knapsack Dynamic Programming
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
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

int dynamic(int **sol, vector<Item> items, int n, int w) {
	int fans; //first answer
	int sans; //second answer
	if (sol[n][w] != -1) {
		return sol[n][w];
	}
	fans = dynamic(sol, items, n - 1, w); //get first answer
	if (items[n - 1].weight <= w) {
		sans = dynamic(sol, items, n - 1, w - items[n - 1].weight) + items[n - 1].profit; //get second answer
	}
	else {
		sans = 0;
	}

	sol[n][w] = max(fans, sans);

	return sol[n][w];

}

int dynamic_fill(int **sol, vector<Item> items, int capacity) {
	int num_items = items.size();
	////pad the 1st row and 1st col with 0
	for (int i = 0; i <= capacity; i++) {
		sol[0][i] = 0;
	}
	for (int i = 0; i <= num_items; i++) {
		sol[i][0] = 0;
	}

	//initialize table with -1
	for (int i = 1; i <= num_items; i++) {
		for (int j = 1; j <= capacity; j++) {
			sol[i][j] = -1;
		}
	}

	//Fill in first row
	for (int i = 1; i <= capacity; i++) {
		if (items[0].weight <= i) {
			sol[1][i] = items[0].profit;
		}
	}


	//Fill in first column
	for (int i = 2; i <= num_items; i++) {
		if (items[i - 1].weight == 1) {
			sol[i][1] = max(items[i - 1].profit, sol[i - 1][1]);
		}
		else {
			sol[i][1] = sol[i - 1][1];
		}

	}

	//Print table to check
	//
	//for(int i = 1; i <= num_items; i++) {
	//	cout << "Row " << i << " ";
	//	for(int j = 1; j <= capacity; j++) {
	//		cout << "Column " << j << ": ";
	//		cout << sol[i][j] << endl;
	//	}
	//}
	return dynamic(sol, items, items.size(), capacity);
}

vector<Item> add_items(int **sol, vector<Item> items, int capacity) {
	vector<Item> items_in_solution;
	int i = items.size(), w = capacity;
	while (i > 0) {
		//if they aren't equal then, we know that it changed at i.
		if (sol[i][w] != sol[i - 1][w]) {
			items_in_solution.push_back(items[i - 1]); //get the item
			w = w - items[i - 1].weight;
		}
		i--;
	}

	return items_in_solution;
}

int main()
{
	int num_items, capacity;
	string input;
	cout << "Knapsack-Dynamic" << endl;
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

	int answer = dynamic_fill(sol, items, capacity);

	//Print table
	//for(int i = 1; i <= num_items; i++) {
		//cout << "Row " << i << " ";
		//for(int j = 1; j <= capacity; j++) {
			//cout << "Column " << j << ": ";
			//cout << sol[i][j] << endl;
		//}
	//}

	int totalWeight = 0;
	vector<Item> items_in_solution = add_items(sol, items, capacity);
	for (int i = 0; i < items_in_solution.size(); i++) {
		cout << items_in_solution[i].id << " " << items_in_solution[i].profit << " " << items_in_solution[i].weight << endl;
		totalWeight = totalWeight + items_in_solution[i].weight;
	}

	cout << "Total Value: " << answer << endl;
	cout << "Total Weight: " << totalWeight << endl;


	for (int i = 0; i <= num_items; i++) {
		delete[] sol[i];
	}
	delete[] sol;

	int pause;
	cin >> pause;

	return 0;
}
