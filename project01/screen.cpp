#include <stdio.h>
#include <windows.h>
#include "screen.h"
#pragma warning(disable:4996)


void gotoxy(int x, int y) {
	COORD coord = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int getx() {
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO a;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	coord.X = a.dwCursorPosition.X;
	return coord.X;
}

int gety() {
	COORD coord;
	CONSOLE_SCREEN_BUFFER_INFO a;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &a);
	coord.Y = a.dwCursorPosition.Y;
	return coord.Y;
}

void delLine(int x) {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	gotoxy(x, gety());

	for (int i = x; i < columns; i++) {
		printf(" ");
	}
}

int consolx() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns, rows;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	
	return columns;
}
void red() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
}

void white() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 
		FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void blue() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
}