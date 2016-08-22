#include "ItemNode.h"
using namespace std;
ItemNode::ItemNode() {
	id = 0;
	profit = 0;
	weight = 0;
	ratio = 0;
	level = 0;
	bound = 0;
}

void ItemNode::setValues(int _id, int _profit, int _weight, double _ratio) {
	id = _id;
	profit = _profit;
	weight = _weight;
	ratio = _ratio;
}
