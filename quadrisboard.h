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

class Level;
class Block;
class Cell;

class QuadrisBoard {
    // Singleton design pattern
    static shared_ptr<QuadrisBoard>instance;
    QuadrisBoard();
    vector<vector<shared_ptr<Cell>>> board; //11x18
    shared_ptr<Block> currentBlock;
    shared_ptr<Level> level;

    bool graphicDisplay;
    //Display display;



public:

    static shared_ptr<QuadrisBoard> getInstance();

    vector<vector<shared_ptr<Cell>>> getBoard();
    void setBoard(vector<vector<shared_ptr<Cell>>> newBoard);

    shared_ptr<Level> getLevel();
    void setLevels(shared_ptr<Level> newLevels);

    shared_ptr<Block> getCurrentBlock();

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
    //Interpreter *patternMatchName(string name); //......add shared ptr

    void replaceBlock(string blockType);

    //~QuadrisBoard();
    void levelUp();
    void levelDown();
    void restart();
    void hint();
    bool isPossible(string command);
};

#endif
