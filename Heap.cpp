#include "Heap.h"
#include "ItemNode.h"
using namespace std;

int Heap::parent(int pos) {
	return pos / 2;
}

int Heap::leftchild(int pos) {
	return 2 * pos;
}

int Heap::rightchild(int pos) {
	return leftchild(pos) + 1;
}

//Swap two nodes
void Heap::swap(int x, int y) {
	ItemNode tmp;
	tmp = PQ[x];
	PQ[x] = PQ[y];
	PQ[y] = tmp;
}

void Heap::bubbleup(int pos) {
	// at the root
	if (pos == 1) {
		return;
	}
	//If the parent position bound is greater than the current position then we are in the correct position.
	if (PQ[parent(pos)].bound >= (PQ[pos].bound)) {
		return;
	}
	swap(pos, parent(pos));//Else if the current position is greater than the parent position, then we need to swap
	bubbleup(parent(pos));//continue doing this recursively
}

ItemNode Heap::getFront() {	
	//If the queue is empty, then we don't want to return anything. PQ[0] has nothing in it
	if (isEmpty()) {
		return PQ[0];
	}
	return PQ[1]; //Get the front of the list which is position 1
}

bool Heap::isFull() {
	return last >= maxSize - 1;
}

bool Heap::isEmpty() {
	return last == 0;//The queue is empty if last is equal to 0
}

void Heap::enqueue(ItemNode node) {

	if (isFull()) {
		return;
	}
	PQ[++last] = node; //Add node to the array
	bubbleup(last); // Find where it should be at in the queue
}

int Heap::countkids(int pos) {
	if (last < leftchild(pos)) {
		return 0;
	}
	if (last == leftchild(pos)) {
		return 1;
	}
	return 2;
}

void Heap::bubbledown(int pos) {
	int numkids = countkids(pos);
	if (numkids == 0) return;
	int largechild = leftchild(pos);
	//if the rightchild is large then the left
	if (numkids > 1 && PQ[rightchild(pos)].bound > (PQ[leftchild(pos)].bound)) {
		largechild = rightchild(pos);
	}
	//If largechild is greater than the current bound then we need to switch the two
	if (PQ[largechild].bound > (PQ[pos].bound)) {
		swap(largechild, pos);//swap the two
		bubbledown(largechild);//continue recurisvely
	}
}

ItemNode Heap::dequeue() {
	if (isEmpty()) {
		return PQ[0];//If the queue is empty, then we don't want to return anything. PQ[0] has nothing in it
	}

	ItemNode rootcopy = PQ[1];
	PQ[1] = PQ[last--];//the new root is the last item in the queue and we will then bubble it down to find its correct position
	bubbledown(1);//bubble down the new root

	return rootcopy;
}
