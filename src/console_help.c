#include <windows.h>

const int COL_GREEN = 2;
const int COL_WHITE = 15;
const int COL_RED = 12;
const int COL_BLUE = 9;

void move(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void colorGreen() {
    color(COL_GREEN);
}

void colorRed() {
    color(COL_RED);
}

void colorBlue() {
    color(COL_BLUE);
}

void colorWhite() {
    color(COL_WHITE);
}

void color(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}