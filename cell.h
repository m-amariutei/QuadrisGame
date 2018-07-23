#ifndef CELL_H
#define CELL_H

#include <memory>
#include "block.h"

class Block;

class Cell {

    int xValue;
    int yValue;
    std::shared_ptr<Block> block;

public:
    Cell(int xValue, int yValue, std::shared_ptr<Block> block);

    std::shared_ptr<Block> getBlock();
    void setBlock(std::shared_ptr<Block> block);

    int getXValue();
    void setXValue(int newX);

    int getYValue();
    void setYValue(int newY);


};

#endif
