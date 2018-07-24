#include "block.h"

Block::Block(vector<shared_ptr<Cell>> cells, char type): cells{cells}, type{type} {
    board = QuadrisBoard::getInstance();
}

vector<shared_ptr<Cell>> Block::getCells() { return cells; }

void Block::setCells(vector<shared_ptr<Cell>> newCells) { cells = newCells; }

char Block::getType() { return type; }

void Block::setType(char newType) { type = newType; }



void Block::right() {
    //create coords
    vector<pair<int,int>> coords;
    for(int i=0; i<cells.size(); i++) {
        coords.push_back(make_pair(cells.at(i)->getYValue(), cells.at(i)->getXValue() + 1));       //row, col
    }
    
    //validate coords
    bool isValid = board->validateCoord(coords);

    //move block to coords
    if(isValid) board->moveBlock(coords);
}

void Block::left() {
     //create coords
    vector<pair<int,int>> coords;
    for(int i=0; i<cells.size(); i++) {
        coords.push_back(make_pair(cells.at(i)->getYValue(), cells.at(i)->getXValue() - 1));       //row, col
    }
    
    //validate coords
    bool isValid = board->validateCoord(coords);

    //move block to coords
    if(isValid) board->moveBlock(coords);
}

bool Block::down() {
    //should always work (if not, generate new block)

    //create coords
    vector<pair<int,int>> coords;
    for(int i=0; i<cells.size(); i++) {
        coords.push_back(make_pair(cells.at(i)->getYValue() + 1, cells.at(i)->getXValue()));       //row, col
    }
    
    //validate coords
    bool isValid = board->validateCoord(coords);

    //move block to coords
    if(isValid) {
        board->moveBlock(coords);
        return true;
    }
    else {
        return false;
    }
}

void Block::drop() {
    //should always work (if not, generate new block)
    while(down());
    
}

void Block::clockwise() {

}

void Block::counter() {

}
