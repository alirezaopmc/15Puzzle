#include "state.h"

state::state(int n) {
	size = n;
	grid = new int*[n];
	for(int i=0; i<4; i++) {
		grid[i] = new int[n];
	}
	empty[0] = empty[1] = -1;
	theI = 0;
	theJ = 0;
}

int state::get(int i, int j) {
	if (i*(i-size) > 0) return -1;
	if (j*(j-size) > 0) return -1;
	return grid[i][j];
}

int state::set(int i, int j, int v) {
	if (i*(i-size) > 0) return -1;
	if (j*(j-size) > 0) return -1;
	if(v == size * size) {
		theI = i;
		theJ = j;
	}
	grid[i][j] = v;
	return 1;
}

int state::swap(int i, int j) {	
	if (i*(i-size) > 0) return -1;
	if (j*(j-size) > 0) return -1;
	int tmp = grid[i][j];
	grid[i][j] = grid[theI][theJ];
	grid[theI][theJ] = tmp;
	theI = i;
	theJ = j;
	return 1;
}

int state::getSize() {
	return size;
}

int state::I() {
	return theI;
}

int state::J() {
	return theJ;
}