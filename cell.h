#ifndef CELL_H
#define CELL_H

#include <memory>
#include <iostream>
#include "block.h"

using namespace std;

class Block;

class Cell {

    int xValue;
    int yValue;
    shared_ptr<Block> block;

public:
    Cell();

    Cell(int xValue, int yValue, shared_ptr<Block> block);

    shared_ptr<Block> getBlock();
    void setBlock(shared_ptr<Block> block);

    int getXValue();
    void setXValue(int newX);

    int getYValue();
    void setYValue(int newY);

};

#endif
