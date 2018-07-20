#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "cell.h"

using namespace std;

class Cell;

class Block {

    vector<Cell*> cells;
    char name;

public:
    Block();

    vector<Cell*> getCells();

    char getName();

    void move(vector<Cell*> newLocation);
    bool validate(vector<Cell*> newLocation);

    ~Block();

};


#endif
