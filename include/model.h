#ifndef MODEL_H
#define MODEL_H

#include <windows.h>

typedef struct Animal {
    int id;
    COORD position;
} Animal;

typedef struct Tree {
    int id;
    COORD position;
} Tree;

#endif