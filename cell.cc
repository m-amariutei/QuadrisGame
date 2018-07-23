#include "cell.h"

int xValue;
int yValue;
shared_ptr<Block> block;

Cell::Cell(int xValue, int yValue, Block* block):
        xValue{xValue}, yValue{yValue}, block{block} {}

Block* Cell::getBlock() {

    return block;
}

void Cell::setBlock(Block* newBlock) {

    block = newBlock;
}

int Cell::getXValue() {

    return xValue;
}

void Cell::setXValue(int newX) {

    xValue = newX;
}

int Cell::getYValue() {

    return  yValue;
}

void Cell::setYValue(int newY) {

    yValue = newY;
}

