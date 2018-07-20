#ifndef CELL_H
#define CELL_H

#include "block.h"

class Cell {

    int xValue;
    int yValue;
    Block * block;

public:
    Cell();

    char getBlockType();

    ~Cell();

};

#endif
