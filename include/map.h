#ifndef MAP_H
#define MAP_H

#include <windows.h>

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

COORD randomizeNextPosition(short x, short y);
void printMapBorders();

#endif