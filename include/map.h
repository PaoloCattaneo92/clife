#ifndef MAP_H
#define MAP_H

#include <windows.h>

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

int isCoordPresent(COORD* array, int size, COORD value);
void randomizeNPositions(COORD* coords, int size);
COORD randomizeFirstPosition();
COORD randomizeNextPosition(short x, short y);
void printMapBorders();

#endif