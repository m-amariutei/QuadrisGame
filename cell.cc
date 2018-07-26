#include "cell.h"

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

void Cell::setXValue(int newX) {
    xValue = newX;
}

int Cell::getYValue() {
    return  yValue;
}

void Cell::setYValue(int newY) {
    yValue = newY;
}

