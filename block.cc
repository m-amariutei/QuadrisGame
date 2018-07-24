#include "block.h"
#include <vector>

Block::Block() {}

Block::Block(vector<shared_ptr<Cell>> cells, char type): cells{cells}, type{type} {}

vector<shared_ptr<Cell>> Block::getCells() { return cells; }

void Block::setCells(vector<shared_ptr<Cell>> newCells) { cells = newCells; }

char Block::getType() { return type; }

void Block::setType(char newType) { type = newType; }

void Block::right() {
    for (int i = 0; i < cells.size(); i++) {

        int current = cells.at(i)->getXValue();
        cells.at(i)->setXValue(++current);
    }
}

void Block::left() {
    for (int i = 0; i < cells.size(); i++) {

        int current = cells[i]->getXValue();
        cells.at(i)->setXValue(--current);
    }
}

void Block::down() {
    for (int i = 0; i < cells.size(); i++) {

        int current = cells.at(i)->getYValue();
        cells.at(i)->setYValue(++current);
    }
}

void Block::drop() {

}
