#include <stdio.h>
#include "../include/map.h"
#include "../include/model.h"
#include "../include/console_help.h"

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 10;
const char TREE_ID[] = "T";
const char WOLF_ID[] = "W";
const char RABBIT_ID[] = "R";

int nearBy(COORD a, COORD b) {
    if(samePosition(a, b) == 1) {
        return 1;
    }

    if(a.X == b.X + 1 && a.Y == b.Y) return 1;
    if(a.X == b.X + 1 && a.Y == b.Y + 1) return 1;
    if(a.X == b.X && a.Y == b.Y + 1) return 1;
    if(a.X == b.X - 1 && a.Y == b.Y + 1) return 1;
    if(a.X == b.X - 1 && a.Y == b.Y) return 1;
    if(a.X == b.X - 1 && a.Y == b.Y - 1) return 1;
    if(a.X == b.X && a.Y == b.Y - 1) return 1;
    if(a.X == b.X + 1 && a.Y == b.Y - 1) return 1;

    return 0;
}

int samePosition(COORD a, COORD b) {
    if(a.X == b.X && a.Y == b.Y) {
        return 1;
    }
    else {
        return 0;
    }
}

int isCoordPresent(COORD* array, int size, COORD value) {
    for (int i = 0; i < size; i++) {
        if (array[i].X == value.X && array[i].Y == value.Y) {
            return 1; // Value is present in the array
        }
    }
    return 0; // Value is not present in the array
}

void randomizeNPositions(COORD* coords, int size) {
    for (int i = 0; i < size; i++) {
        COORD randomCoord;
        do {
            randomCoord.X = (rand() % (MAP_WIDTH -2)) + 1;
            randomCoord.Y = (rand() % (MAP_HEIGHT -2)) + 1;
        } while (isCoordPresent(coords, i, randomCoord));

        coords[i] = randomCoord;
    }
}


COORD randomizeNextPosition(short x, short y) {
    int randomDirection = rand() % 8; // Generate a random number between 0 and 7
    
    switch (randomDirection) {
        case 0: x += 1; break;         // Move right
        case 1: x -= 1; break;         // Move left
        case 2: y += 1; break;         // Move down
        case 3: y -= 1; break;         // Move up
        case 4: x += 1; y += 1; break; // Move down-right (diagonal)
        case 5: x -= 1; y += 1; break; // Move down-left (diagonal)
        case 6: x += 1; y -= 1; break; // Move up-right (diagonal)
        case 7: x -= 1; y -= 1; break; // Move up-left (diagonal)
    }

    if(x >= MAP_WIDTH - 1) {
        x = MAP_WIDTH - 2;
    }
    if(y >= MAP_HEIGHT - 1) {
        y = MAP_HEIGHT - 2;
    }
    if(x <= 0) {
        x = 1;
    }
    if(y <= 0) {
        y = 1;
    }

    COORD result = { x, y };
    return result;
}

void moveRabbitTo(Rabbit* animal, COORD newPosition, Tree* trees, size_t treeSize) {
    int collision = 0;
    for (size_t i = 0; i < treeSize; i++)
    {
        if(newPosition.X == trees[i].position.X && newPosition.Y == trees[i].position.Y) {
            collision = 1;
            break;
        }
    }

    if(collision) {
        // do not move animal if collides with a tree
        return;
    }
    
    
    move(animal->position.X, animal->position.Y);
    printf(" ");
    animal->position.X = newPosition.X;
    animal->position.Y = newPosition.Y;
    move(animal->position.X, animal->position.Y);
    colorBlue();
    printf(RABBIT_ID);
}

void moveWolfTo(Wolf* wolf, COORD newPosition, Tree* trees, size_t treeSize) {
    int collision = 0;
    wolf->hunger++;
    
    for (size_t i = 0; i < treeSize; i++)
    {
        if(newPosition.X == trees[i].position.X && newPosition.Y == trees[i].position.Y) {
            collision = 1;
            break;
        }
    }

    if(collision) {
        // do not move wolf if collides with a tree
        return;
    }
    
    
    move(wolf->position.X, wolf->position.Y);
    printf(" ");
    wolf->position.X = newPosition.X;
    wolf->position.Y = newPosition.Y;
    move(wolf->position.X, wolf->position.Y);
    colorRed();
    printf(WOLF_ID);
}

void printTrees(Tree trees[], size_t size) {
    for (size_t i = 0; i < size; i++)
    {
        Tree tree = trees[i];
        move(tree.position.X, tree.position.Y);
        colorGreen();
        printf(TREE_ID);
    }
}

void printAnimals(Wolf animals[], size_t size) {
    for (size_t i = 0; i < size; i++)
    {
        Wolf animal = animals[i];
        move(animal.position.X, animal.position.Y);
        colorRed();
        printf(WOLF_ID);
    }
}

void printMapBorders() {
    colorWhite();
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {

            move(x, y);
            if(x == 0 || x == MAP_WIDTH - 1) {
                if(y == 0) {
                    printf("+");
                    continue;
                }
                if(y == MAP_HEIGHT-1) {
                    printf("+");
                    continue;
                }

                printf("|");
                continue;
            }

            if(y == 0 || y == MAP_HEIGHT-1) {
                printf("-");
            }
        }
        printf("\n");
    }
    return;
}