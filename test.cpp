#include <iostream>
#include <Windows.h>
#include <conio.h>
void gotoXY(int x, int y) {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorCoord;
	cursorCoord.X = x;
	cursorCoord.Y = y;
	SetConsoleCursorPosition(consoleHandle, cursorCoord);
}
int main() {
	int c = 1;
	while(c != '0') {
		c = getch();
		if (c == 224) {
			c = getch();
		}
		std::cout << c << std::endl;
	}
}