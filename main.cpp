#include <iostream>
#include <fstream>
#include <conio.h>
#include <Windows.h>
#include "./state/state.h"

#define MAP_SIZE 0
#define MAP_FILE 1

#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

#define EXIT 0
#define REPEAT -1
#define RUNNING 1
#define WIN 2

using namespace std;

void gotoXY(int x, int y);
state* loadMap(string path);

void start(state* game);
int run(state* game);
void showState(state* game);
int getInput();
int handle(state* game, int dir);
int terminateGame();
void clrsrc();
void initConsole(int n);

int main(){
	// int mode;
	// int n;
	// string path;

	// string cmd;
	// cout << "Start a new game" << endl;
	// cout << "1. Enter the size of the map grid" << endl;
	// cout << "2. Enter the path to the map file" << endl;
	// cout << "Otherwise program will be terminated." << endl;
	// cin >> cmd;

	// if (cmd == "1") {
	// 	mode = MAP_SIZE;
	// 	map_size:
	// 	cout << "Enter a number between 3 and 8: ";
	// 	cin >> cmd;
	// 	if (cmd.length() == 1 && cmd[0] >= '0' && cmd[0] <= '9') {
	// 		n = cmd[0] - '0';
	// 	} else {
	// 		goto map_size;
	// 	}
	// }

	// if (cmd == "2") {
	// 	mode = MAP_FILE;
	// 	file_path:
	// 	cout << "Enter the path of the map file: ";
	// 	cin >> path;
	// 	ifstream file;
	// 	file.open(path.c_str());
	// 	if (file) {
	// 		file >> n;
	// 	} else {
	// 		goto file_path;
	// 	}
	// }

	// state* game;

	// if (mode == MAP_SIZE) {
	// 	game = new state(n);
	// }

	// if (mode == MAP_FILE) {
	// 	game = loadMap(path);
	// }

	// start(game);

	state* game = new state(4);

	game->set(0, 0, 1);
	game->set(0, 1, 2);
	game->set(0, 2, 3);
	game->set(0, 3, 4);
	game->set(1, 0, 5);
	game->set(1, 1, 16);
	game->set(1, 2, 6);
	game->set(1, 3, 7);
	game->set(2, 0, 10);
	game->set(2, 1, 11);
	game->set(2, 2, 12);
	game->set(2, 3, 8);
	game->set(3, 0, 9);
	game->set(3, 1, 13);
	game->set(3, 2, 14);
	game->set(3, 3, 15);

	// for(int i = 0; i < game->getSize(); i++) {
	// 	for(int j = 0; j < game->getSize(); j++) {
	// 		cout << game->get(i, j) << " ";
	// 	}
	// 	cout << endl;
	// }

	start(game);
}

void gotoXY(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = x;
	cursorCoord.Y = y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}

state* loadMap(string path) {
	ifstream file;
	file.open(path.c_str());

	int n;
	file >> n;

	cout << n << endl;

	state* game = new state(n);

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			int v;
			file >> v;
			game->set(i, j, v);
		}
	}

	return game;
}

void start(state* game) {
	clrsrc();
	initConsole(game->getSize());

	int state = RUNNING;
	while(state == RUNNING) {
		state = run(game);
	};

	if (state == EXIT) {
		cout << "Exited!\n";
	}

	if (state == WIN) {
		showState(game);
		cout << "You won! Wp :)";
	}
}

int run(state* game) {
	showState(game);
	int input = getInput();
	while (input == REPEAT) input = getInput();
	if (input == EXIT) {
		return terminateGame();
	} else {
		return handle(game, input);
	}
}

void showState(state* game) {
	int n = game->getSize();
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			gotoXY(5*j+2, 2*i+1);
			if (game->get(i, j) == n * n) {
				cout << "  ";
			} else {
				if (game->get(i, j) < 10) cout << " ";
				cout << game->get(i, j);
			}
		}
	}
	gotoXY(0, 9);
}

int getInput() {
	int c = getch();
	if (c == 224) {
		int k = getch();
		if (k == 75) return LEFT;
		if (k == 72) return UP;
		if (k == 77) return RIGHT;
		if (k == 80) return DOWN;
		return REPEAT;
	}

	if (c == '0') return EXIT;
	return REPEAT;
}

int handle(state* game, int dir) {
	if (dir == LEFT && game->J()-1 >= 0) {
		if (game->swap(game->I(), game->J()-1) == -1) {
			cout << "GLITCHED !" << endl;
			return EXIT;
		}
	}

	if (dir == UP && game->I()-1 >= 0) {
		if (game->swap(game->I()-1, game->J()) == -1) {
			cout << "GLITCHED !" << endl;
			return EXIT;
		}
	}

	if (dir == RIGHT && game->J()+1 < game->getSize()) {
		if (game->swap(game->I(), game->J()+1) == -1) {
			cout << "GLITCHED !" << endl;
			return EXIT;
		}
	}

	if (dir == DOWN && game->I()+1 < game->getSize()) {
		if (game->swap(game->I()+1, game->J()) == -1) {
			cout << "GLITCHED !" << endl;
			return EXIT;
		}
	}

	int n = game->getSize();
	int k = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			if (game->get(i, j) != ++k) return RUNNING;
		}
	}

	return WIN;
}

int terminateGame() {
	cout << "Terminated!";
	return EXIT;
}

void clrsrc() {
	system("cls");
}

void initConsole(int n) {
	string line = 		"=====================\n";
	string blank_line = "|    |    |    |    |\n";
	cout << line <<
			blank_line << line <<
			blank_line << line <<
			blank_line << line <<
			blank_line << line;
}
