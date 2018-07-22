#ifndef CELL_H
#define CELL_H

#include "block.h"

class Block;

class Cell {

    int xValue;
    int yValue;
    Block * block;

public:
    Cell();

    Block * getBlock();
    void setBlock(Block *block);

    int getXValue();
    int getYValue();

    char getBlockType();

    ~Cell();

};

#endif
