#include "cell.h"

int xValue;
int yValue;
shared_ptr<Block> block;

Cell::Cell(int xValue, int yValue, shared_ptr<Block> block):
        xValue{xValue}, yValue{yValue}, block{block} {}

shared_ptr<Block> Cell::getBlock() {

    return block;
}

void Cell::setBlock(shared_ptr<Block> newBlock) {

    block = newBlock;
}

int Cell::getXValue() {

    return xValue;
}

int Cell::getYValue() {

    return  yValue;
}

char Cell::getBlockType() {

    return block->getType();
}
