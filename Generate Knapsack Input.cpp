//Eric Sanders
//Algorithms
//Generate text files for Project Entrapment
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <math.h>       /* log2 */
using namespace std;

int main()
{
	
	srand(time(NULL));
	int size=0;
	cout << "Enter the number of items: ";
	cin >> size;

	int weight[4];
	weight[0] = 2*size;
	weight[1] = size*log2(size);
	weight[2] = size*size;
	weight[3] = (size*size)*log2(size);
	for(int j = 0; j < 4; j++) {
		stringstream ss;//create a stringstream
		ss << "input" << size << "-" << weight[j] << ".txt";//add number to the stream
		string input = ss.str();
		ofstream fileout(input.c_str());
		fileout << size << " " << weight[j] << endl;
		for(int i = 1; i <= size; i++) {
			fileout << i << " " << ((1 + rand() % size) * 5) << " " << (1 + rand() % (3 * size)) << endl;
		}
	}
	
	return 0;
}

	
	