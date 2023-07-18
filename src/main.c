#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include "../include/map.h"
#include "../include/model.h"
#include <time.h>

const unsigned int GAME_TICK = 250 * 1000; //ms * 1000 => microseconds 

Animal animals[] = {
    {1, {2, 3} },
    {2, {5, 1} },
    {3, {6, 8} }
};

Tree trees[] = {
    {1, {6, 7} },
    {2, {1, 4} },
    {3, {10, 8} }
    };

void gameStep() {
    size_t animalSize = sizeof(animals) / sizeof(animals[0]);
    size_t treeSize = sizeof(trees) / sizeof(trees[0]);

    for (size_t i = 0; i < animalSize; i++)
    {
        short x = animals[i].position.X;
        short y = animals[i].position.Y;
        moveAnimalTo(&animals[i], randomizeNextPosition(x, y), trees, treeSize);
    }
}

int main() {
    srand(time(NULL));

    printMapBorders();

    size_t size = sizeof(trees) / sizeof(trees[0]);
    printTrees(trees, size);

    size = sizeof(animals) / sizeof(animals[0]);
    printAnimals(animals, size);

    while(1) {
        gameStep();
        usleep(GAME_TICK);
    }

    move(0, MAP_HEIGHT + 2);
    system("PAUSE");
    return 0;
}