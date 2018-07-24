#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>
#include <memory>
#include "cell.h"
#include "quadrisboard.h"

using namespace std;

enum BlockType {
    Iblock, Jblock, Lblock, Oblock, Sblock, Tblock, Zblock, Single
};

class Cell;
class QuadrisBoard;

class Block {
    shared_ptr<QuadrisBoard> board;
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
    void drop();
    bool down();
    void clockwise();
    void counter();

    //virtual shared_ptr<Block> create(BlockType bType) = 0;

};


#endif
