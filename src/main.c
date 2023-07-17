#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <windows.h>
#include "../include/map.h"
#include "../include/tree.h"
#include "../include/animal.h"

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
    size_t size = sizeof(animals) / sizeof(animals[0]);
    for (size_t i = 0; i < size; i++)
    {
        Animal animal = animals[i];
        COORD newPosition;
        newPosition.X = animal.position.X + 1;
        newPosition.Y = animal.position.Y + 1;
        moveAnimalTo(animal, newPosition);
    }
    
}

int main() {
    printMapBorders();

    size_t size = sizeof(trees) / sizeof(trees[0]);
    printTrees(trees, size);

    size = sizeof(animals) / sizeof(animals[0]);
    printAnimals(animals, size);

    while(1) {
        gameStep();
        sleep(1);
    }

    move(0, MAP_HEIGHT + 2);
    system("PAUSE");
    return 0;
}