#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "cell.h"

using namespace std;

class Block {

    vector<Cell *> cells;
    char name;

public:
    Block();

    void move(vector<Cell*> newLocation)();
    bool validate(vector<Cell*> newLocation)();

    ~Block();

};


#endif BLOCK_H
