//Eric Sanders
//Branch && Bound Algorithm for the 0-1 Knapsack Problem

#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include "ItemNode.h"
#include "Heap.h"
using namespace std;


struct greater_ratio {
	inline bool operator() (const ItemNode& node1, const ItemNode& node2) {
		return (node1.ratio > node2.ratio);
	}
};

//Computes the bound of a node
double bound(ItemNode u, vector<ItemNode> nodes, int n, int capacity) {
	double result;
	// If the weight of the node is greater than the capicty, then return
	if (u.weight >= capacity) {
		return 0;
	}
	else {
		result = u.profit;
		int j = u.level + 1;
		int totalWeight = u.weight;
		// grab as many items as possible
		while ((j < n) && (totalWeight + nodes[j].weight <= capacity)) {
			totalWeight = totalWeight + nodes[j].weight;
			result = result + nodes[j].profit;
			j++;//contine to go to the next child
		}
		if (j < n) {
			result = result + (capacity - totalWeight) * ((double)nodes[j].profit / (double)nodes[j].weight); //Grab fraction of the item
		}
		return result;
	}
}

void knapsack(Heap heap, vector<ItemNode> nodes, int n, int capacity, int &maxProfit) {
	ItemNode u, v;
	v.level = -1;//Empty
	v.profit = 0;
	v.weight = 0;
	v.bound = bound(v, nodes, n, capacity);

	heap.enqueue(v);
	while (heap.isEmpty() == false) {
		v = heap.dequeue();//Remove node with best bound
		//Check if node is still promising
		if(v.bound > maxProfit) {
			u.level = v.level + 1;//set u to the child that includes the next item
			u.weight = v.weight + nodes[u.level].weight;
			u.profit = v.profit + nodes[u.level].profit;

			//Change the maxprofit if node u's profit is larger and weight is <= capacity
			if ((u.weight <= capacity) && (u.profit > maxProfit)) {
				maxProfit = u.profit;
			}
			u.bound = bound(u, nodes, n, capacity);
			//Include child
			if (u.bound > maxProfit) {
				heap.enqueue(u);
			}
			//Don't include child
			u.weight = v.weight;
			u.profit = v.profit;
			u.bound = bound(u, nodes, n, capacity);
			if (u.bound > maxProfit) {
				heap.enqueue(u);
			}
		}
	}
}

int main() {
	string input;
	int n, capacity;
	cout << "Enter the filename: ";
	cin >> input;
	ifstream filein(input.c_str());
	filein >> n >> capacity;
	vector<ItemNode> nodes;
	int node_id;
	int profit;
	int weight;
	Heap heap;

	ItemNode node;
	for (int i = 0; i < n; i++) {
		filein >> node_id >> profit >> weight;
		node.setValues(node_id, profit, weight, ((double)profit / (double)weight));
		nodes.push_back(node);
	}
	
	sort(nodes.begin(), nodes.end(), greater_ratio());
	int maxProfit = 0;
	knapsack(heap, nodes, n, capacity, maxProfit);
	cout << maxProfit << endl;
	int pause;
	cin >> pause;
	
	return 0;
}