#include "cell.h"

Cell::Cell() {} /// TO DO

Block * Cell::getBlock() {

    return block;
}

void Cell::setBlock(Block *newBlock) {

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

Cell::~Cell() {}