#ifndef QUADRISBOARD_H
#define QUADRISBOARD_H

#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "cell.h"
#include "interpreter.h"
#include "level.h"
#include "constants.h"
#include "block.h"
#include "display.h"

using namespace std;

class Interpreter;
class Level;

class QuadrisBoard {
    // Singleton design pattern
    static shared_ptr<QuadrisBoard> instance;
    QuadrisBoard();
    vector<vector<shared_ptr<Cell>>> board; //11x18
    vector<shared_ptr<Block>> blocksOnBoard;
    int currentBlockIndex;
    shared_ptr<Level> level;

    bool graphicDisplay;
    //Display display;



public:

    static shared_ptr<QuadrisBoard> getInstance();

    vector<vector<shared_ptr<Cell>>> getBoard();
    void setBoard(vector<vector<shared_ptr<Cell>>> newBoard);

    vector<shared_ptr<Block>> getBlocksOnBoard();
    void setBlocksOnBoard(vector<shared_ptr<Block>> newBlocksOnBoard);

    std::shared_ptr<Level> getLevels();
    void setLevels(shared_ptr<Level> newLevels);


    void initialize();
    bool isLost();
    void print(bool seeInvisible = true);
    void executeCommand(string name);
    bool isFullRow(int rowIndex);
    void clearRow(int rowIndex);
    void dropRowsAbove(int rowIndex);
    void dropTop(int rowIndex, int colIndex);
    bool isBlockStuck(shared_ptr<Block>);
    bool deleteCellFromBlock(shared_ptr<Block>, int, int);
    bool cellBelowIsSticky(shared_ptr<Block>, int, int);
    Interpreter *patternMatchName(string name); //......add shared ptr

    ~QuadrisBoard();

};

#endif
