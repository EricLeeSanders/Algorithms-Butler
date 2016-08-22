#pragma once
class ItemNode
{

	public:
		int id;
		int profit;
		int weight;
		int level;
		double ratio;
		double bound;
		void setValues(int _id, int _profit, int _weight, double _ratio);
		ItemNode();
};

