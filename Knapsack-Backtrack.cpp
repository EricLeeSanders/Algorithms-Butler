////Eric Sanders
////Knapsack with Backtracking

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
using namespace std;

/*
Represents an item that has an id, profit, weight, and ratio
*/
class Item {
public:
	int id, profit, weight;
	double ratio;

	void setValues(int _id, int _profit, int _weight, double _ratio) {
		id = _id;
		profit = _profit;
		weight = _weight;
		ratio = _ratio;
	}
};

struct greater_ratio {
	inline bool operator() (const Item& item1, const Item& item2) {
		return (item1.ratio > item2.ratio);
	}
};

void Knapsack_rec(int i, int profit, int weight, vector<Item> items, vector<char> included, vector<char> &bestSet, int &maxProfit, int capacity);
bool Promising(int i, int profit, int weight, vector<Item> items, int maxProfit, int capacity);



/*
Recursively finds the best set of items. 
*/
void Knapsack_rec(int i, int profit, int weight, vector<Item> items, vector<char> included, vector<char> &bestSet, int &maxProfit, int capacity) {
	//If we find a better set, update to keep track of the best found so far
	if ((weight <= capacity) && (profit > maxProfit)) { 
		maxProfit = profit;
		bestSet = included;
	}

	//if the current item is promising
	if (Promising(i, profit, weight, items, maxProfit, capacity)) {
		included.push_back('y'); 
		Knapsack_rec(i + 1, (profit + items[i].profit), (weight + items[i].weight), items, included, bestSet, maxProfit, capacity); //Move to next item
		included[i] = 'n';
		Knapsack_rec(i + 1, profit, weight, items, included, bestSet, maxProfit, capacity); // Move to next item without including this item
	}
}
/*
Starts the recursive knapsack function
*/
void Knapsack(vector<Item> items, vector<char> &bestSet, int &maxProfit, int capacity) {
	vector<char> included;
	Knapsack_rec(0,0,0, items, included, bestSet, maxProfit, capacity);
}

/*
Checks to see if the item is promising.
*/
bool Promising(int i, int profit, int weight, vector<Item> items, int maxProfit, int capacity) {
	if (weight >= capacity) {
		return false;
	}

	int totalWeight;
	double bound;

	bound = profit; 
	totalWeight = weight;
	while ((i < items.size()) && (totalWeight + items[i].weight <= capacity)) {
		totalWeight = totalWeight + items[i].weight;
		bound = bound + items[i].profit;
		i++;
	}
	if (i < items.size()) {
		bound = bound + (double(capacity - totalWeight) * ((double)items[i].profit / (double)items[i].weight));
	}
	return (bound > maxProfit);
}

int main() {
	string input;
	cout << "Knapsack-Backtrack" << endl;
	cout << "Enter the filename: ";
	cin >> input;
	ifstream filein(input.c_str());
	int n, capacity;
	filein >> n >> capacity;

	vector<Item> items;
	int item_id;
	int profit;
	int weight;

	for (int i = 0; i < n; i++)	{
		filein >> item_id >> profit >> weight;
		Item item;
		item.setValues(item_id, profit, weight, ((double)profit / (double)weight));
		items.push_back(item);
	}
	sort(items.begin(), items.end(), greater_ratio());
	int maxProfit;
	vector<char> bestSet;
	Knapsack(items, bestSet, maxProfit, capacity);
	for (int i = 0; i < bestSet.size(); i++) {
		if (bestSet[i] == 'y')
			cout << items[i].id << " " << items[i].profit << " " << items[i].weight << endl;
	}
	cout << "Backtrack Total Value: " << maxProfit << endl;

	int pause;
	cin >> pause;

	return 0;
}
