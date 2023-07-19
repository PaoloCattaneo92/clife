#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include "../include/map.h"
#include "../include/model.h"
#include <time.h>

const unsigned int GAME_TICK = 250 * 1000; //ms * 1000 => microseconds 
const int WOLF_COUNT = 3;
const int RABBIT_COUNT = 5;
const int TREE_COUNT = 6;
const int TOTAL_COUNT = WOLF_COUNT + RABBIT_COUNT + TREE_COUNT;

Wolf* wolves;
Rabbit* rabbits;
Tree* trees;

void gameStep() {
    for (int i = 0; i < WOLF_COUNT; i++)
    {
        short x = wolves[i].position.X;
        short y = wolves[i].position.Y;
        moveWolfTo(&wolves[i], randomizeNextPosition(x, y), trees, TREE_COUNT);
    }

    for (int i = 0; i < RABBIT_COUNT; i++)
    {
        short x = rabbits[i].position.X;
        short y = rabbits[i].position.Y;
        moveRabbitTo(&rabbits[i], randomizeNextPosition(x, y), trees, TREE_COUNT);
    }
}

void prepareData() {
    wolves = (Wolf*)malloc(WOLF_COUNT * sizeof(Wolf));
    trees = (Tree*)malloc(TREE_COUNT * sizeof(Tree));
    rabbits = (Rabbit*)malloc(RABBIT_COUNT * sizeof(Rabbit));

    COORD* coords = (COORD*)malloc(TOTAL_COUNT * sizeof(COORD));
    randomizeNPositions(coords, TOTAL_COUNT);
    
    int j = 0;
    for(int i = 0; i< WOLF_COUNT; i++) {
        wolves[i].id = i+1;
        wolves[i].position.X = coords[j].X;
        wolves[i].position.Y = coords[j].Y;
        j++;
    }

    for(int i = 0; i< TREE_COUNT; i++) {
        trees[i].id = i+1;
        trees[i].position.X = coords[j].X;
        trees[i].position.Y = coords[j].Y;
        j++;
    }

    for(int i = 0; i< RABBIT_COUNT; i++) {
        rabbits[i].id = i+1;
        rabbits[i].position.X = coords[j].X;
        rabbits[i].position.Y = coords[j].Y;
        j++;
    }

    free(coords);
}

int main() {
    srand(time(NULL));

    prepareData();

    printMapBorders();

    printTrees(trees, TREE_COUNT);
    printAnimals(wolves, WOLF_COUNT);

    while(1) {
        gameStep();
        usleep(GAME_TICK);
    }

    move(0, MAP_HEIGHT + 2);
    system("PAUSE");
    return 0;
}