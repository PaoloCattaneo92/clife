#include <stdio.h>
#include "../include/map.h"
#include "../include/tree.h"
#include "../include/animal.h"
#include "../include/console_help.h"

const int MAP_WIDTH = 30;
const int MAP_HEIGHT = 10;
const char TREE_ID[] = "T";
const char ANIMAL_ID[] = "V";

void moveAnimalTo(Animal animal, COORD newPosition) {
    move(animal.position.X, animal.position.Y);
    printf(" ");
    animal.position.X = newPosition.X;
    animal.position.Y = newPosition.Y;
    move(animal.position.X, animal.position.Y);
    colorRed();
    printf(ANIMAL_ID);
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

void printAnimals(Animal animals[], size_t size) {
    for (size_t i = 0; i < size; i++)
    {
        Animal animal = animals[i];
        move(animal.position.X, animal.position.Y);
        colorRed();
        printf(ANIMAL_ID);
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