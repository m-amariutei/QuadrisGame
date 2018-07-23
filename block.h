#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "cell.h"

using namespace std;

enum BlockType {
    Iblock, Jblock, Lblock, Oblock, Sblock, Tblock, Zblock, Single
};

class Cell;

class Block {
protected:
    vector<Cell*> cells;
    char type;

public:
    Block(vector<Cell*> cells, char type);

    vector<Cell*> getCells();
    void setCells(vector<Cell*> newCells);

    char getType();
    void setType(char newType);

    void right();
    void left();
    void drop();
    virtual void clockwise() = 0;
    virtual void counter() = 0;

    //virtual shared_ptr<Block> create(BlockType bType) = 0;

};


#endif
