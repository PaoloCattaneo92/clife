#ifndef MAP_H
#define MAP_H

#include <windows.h>
#include "model.h"

extern const int MAP_WIDTH;
extern const int MAP_HEIGHT;

void printAnimals(Wolf animals[], size_t size);
void printTrees(Tree trees[], size_t size);
int samePosition(COORD a, COORD b);
void moveWolfTo(Wolf* animal, COORD newPosition, Tree* trees, size_t treeSize);
void moveRabbitTo(Rabbit* animal, COORD newPosition, Tree* trees, size_t treeSize);
int isCoordPresent(COORD* array, int size, COORD value);
void randomizeNPositions(COORD* coords, int size);
COORD randomizeFirstPosition();
COORD randomizeNextPosition(short x, short y);
void printMapBorders();

#endif