#ifndef _STATE_
#define _STATE_

#include <iostream>
using namespace std;

class state {
private:
	int size;
	int** grid;
	int empty[2];
	int theI, theJ;
public:
	state(int n);
	int get(int i, int j);
	int set(int i, int j, int v);
	int swap(int i, int j);
	int getSize();
	int I();
	int J();
};

#endif
