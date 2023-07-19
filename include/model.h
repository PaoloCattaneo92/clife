#ifndef MODEL_H
#define MODEL_H

#include <windows.h>

typedef struct Rabbit {
    int id;
    COORD position;
} Rabbit;

typedef struct Wolf {
    int id;
    COORD position;
    int hunger;
} Wolf;

typedef struct Tree {
    int id;
    COORD position;
} Tree;

#endif