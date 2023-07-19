#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include "../include/map.h"
#include "../include/model.h"
#include <time.h>
#include "../include/console_help.h"
#include "../include/log.h"

const unsigned int GAME_TICK = 100 * 1000; //ms * 1000 => microseconds 
#define MAX_WOLF 20
#define MAX_RABBIT 20
const int MAX_HUNGER = 25;

int wolfCount = 3;
int rabbitCount = 5;
int treeCount = 6;
int eventCount = 0;

Wolf wolves[MAX_WOLF];
Rabbit rabbits[MAX_RABBIT];
Tree* trees;

int totalCount() {
    return wolfCount + rabbitCount + treeCount;
}

void moveWolves() {
    for (int i = 0; i < wolfCount; i++)
    {
        short x = wolves[i].position.X;
        short y = wolves[i].position.Y;
        moveWolfTo(&wolves[i], randomizeNextPosition(x, y), trees, treeCount);
    }
}

void moveRabbits() {
    for (int i = 0; i < rabbitCount; i++)
    {
        short x = rabbits[i].position.X;
        short y = rabbits[i].position.Y;
        moveRabbitTo(&rabbits[i], randomizeNextPosition(x, y), trees, treeCount);
    }
}

void handleInteractions() {
    // Wolf + Rabbit -> Wolf eats the rabbit and create a new wolf

    int* eatenRabbitsIds = (int*)malloc(rabbitCount * sizeof(int));
    COORD* newWolfPositions = (COORD*)malloc(wolfCount * sizeof(int));
    int eaten = 0;


    move(0, MAP_HEIGHT + 2 + eaten);
    
    for (int i = 0; i < wolfCount; i++) {
        for(int j = 0; j < rabbitCount; j++) {

            if(samePosition(wolves[i].position, rabbits[j].position) == 1) {
                // eating wolf is no more hungry
                wolves[i].hunger = 0;

                // rabbit is eaten
                eaten++;
                eatenRabbitsIds[eaten] = rabbits[j].id;
                newWolfPositions[eaten] = wolves[i].position;
            }
        }
    }

    for(int i = 0; i < eaten; i++) {

        // // remove eaten rabbit
        // int eatenRabbitId = eatenRabbitsIds[i];
        // int indexToRemove = 0;
        // for(int j = 0; j < rabbitCount; j++) {
        //     if(rabbits[j].id == eatenRabbitId) {
        //         indexToRemove = j;
        //         break;
        //     }
        // }

        // for (int i = indexToRemove; i < rabbitCount - 1; i++) {
        //     rabbits[i] = rabbits[i + 1];
        // }
        // rabbitCount--;

        // new wolf is born
        if(wolfCount < MAX_WOLF - 1) {
            wolfCount++;
            wolves[wolfCount -1].id = wolfCount;
            wolves[wolfCount -1].position.X = newWolfPositions[i].X;
            wolves[wolfCount -1].position.Y = newWolfPositions[i].Y;
        }
    }

    free(newWolfPositions);
    free(eatenRabbitsIds);

    // Rabbit + Rabbit -> Rabbit mates and a new rabbit is born
    int nearbyCount = rabbitCount;
    int* nearbies = (int*)malloc(nearbyCount * sizeof(int));
    
    for (int i = 0; i < rabbitCount; i++) {
        for(int j = 0; j < rabbitCount; j++) {
            if(i == j) {
                continue;
            }

            if(samePosition(rabbits[i].position, rabbits[j].position) == 1) {
                if(rabbitCount == MAX_RABBIT - 1) {
                    // too many rabbits already
                    continue;
                }

                nearbies[i] = 1;
            }
        }
    }

    for(int i = 0; i< nearbyCount; i++) {
        if(nearbies[i] == 1 && rabbitCount < MAX_RABBIT - 1) {

            rabbitCount++;
            rabbits[rabbitCount -1].id = rabbitCount;
            rabbits[rabbitCount -1].position.X = rabbits[i].position.X;
            rabbits[rabbitCount -1].position.Y = rabbits[i].position.Y;
        }
    }

    free(nearbies);
}

void handleHunger() {
     // Wolf + Rabbit -> Wolf eats the rabbit and create a new wolf
    for (int j = 0; j < wolfCount; j++) {
        if(wolves[j].hunger > MAX_HUNGER) {
            // wolf starves to deaths
            move(wolves[j].position.X, wolves[j].position.Y);
            printf(" ");

            int indexToRemove = j;
            for (int i = indexToRemove; i < wolfCount - 1; i++) {
                wolves[i] = wolves[i + 1];
            }
            wolfCount--;
        }
    }
}

void printData() {
    move(0, MAP_HEIGHT + 2);
    colorWhite();
    printf("Wolves: ");
    colorRed();
    printf("%d", wolfCount);
    colorWhite();
    printf("\nRabbits: ");
    colorBlue();
    printf("%d", rabbitCount);
}

void gameStep() {
    log("*** Launching wolf vs rabbits simulation *** ");
    log("Current configuration: ");
    log("MAP_WIDTH: %d", MAP_WIDTH);
    log("MAP_HEIGHT: %d", MAP_HEIGHT);

    moveWolves();
    moveRabbits();

    handleInteractions();
    handleHunger();

    printData();
}

void prepareData() {
    // wolves = (Wolf*)malloc(wolfCount * sizeof(Wolf));
    trees = (Tree*)malloc(treeCount * sizeof(Tree));
    //rabbits = (Rabbit*)malloc(rabbitCount * sizeof(Rabbit));

    COORD* coords = (COORD*)malloc(totalCount() * sizeof(COORD));
    randomizeNPositions(coords, totalCount());
    
    int j = 0;
    for(int i = 0; i< wolfCount; i++) {
        wolves[i].id = i+1;
        wolves[i].position.X = coords[j].X;
        wolves[i].position.Y = coords[j].Y;
        j++;
    }

    for(int i = 0; i< treeCount; i++) {
        trees[i].id = i+1;
        trees[i].position.X = coords[j].X;
        trees[i].position.Y = coords[j].Y;
        j++;
    }

    for(int i = 0; i< rabbitCount; i++) {
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

    printTrees(trees, treeCount);
    printAnimals(wolves, wolfCount);

    while(1) {
        gameStep();
        usleep(GAME_TICK);
    }

    move(0, MAP_HEIGHT + 2);
    system("PAUSE");
    return 0;
}