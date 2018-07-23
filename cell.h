#ifndef CELL_H
#define CELL_H

#include <memory>
#include "block.h"

class Block;

class Cell {

    int xValue;
    int yValue;
    Block* block;

public:
    Cell();

    Cell(int xValue, int yValue, Block* block);

    Block* getBlock();
    void setBlock(Block* block);

    int getXValue();
    void setXValue(int newX);

    int getYValue();
    void setYValue(int newY);


};

#endif
