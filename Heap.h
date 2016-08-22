#pragma once
#include "ItemNode.h";
using namespace std;
class Heap
{

	private:
		ItemNode PQ[10000];
		int maxSize = 10000;
		int last = 0;
	public:
		int parent(int pos);
		int leftchild(int pos);
		int rightchild(int pos);
		void swap(int x, int y);
		void bubbleup(int pos);
		ItemNode getFront();
		bool isFull();
		bool isEmpty();
		void enqueue(ItemNode node);
		int countkids(int pos);
		void bubbledown(int pos);
		ItemNode dequeue();
};

