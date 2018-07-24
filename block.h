#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include <iostream>
#include <memory>
#include <algorithm>
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

    bool right();
    bool left();
    void drop();
    bool down();
    bool clockwise();
    bool counter();
    bool rotate(vector<int> values);
    pair<int,int> getMinMaxElements(bool isX);

    //virtual shared_ptr<Block> create(BlockType bType) = 0;

};


#endif
