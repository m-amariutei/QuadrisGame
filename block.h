#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "cell.h"

using namespace std;

enum BlockType {
    Iblock, Jblock, Lblock, Oblock, Sblock, Tblock, Zblock
};

class Cell;

class Block {

    vector<shared_ptr<Cell>> cells;
    char type;

public:
    Block(vector<shared_ptr<Cell>> cells, char type);

    vector<shared_ptr<Cell>> getCells();
    void setCells(vector<shared_ptr<Cell>> newCells);

    char getType();
    void setType(char newType);

    void right();
    void left();
    void down();
    virtual void clockwise() = 0;
    virtual void counter() = 0;

    //virtual shared_ptr<Block> create(BlockType bType) = 0;

};


#endif
