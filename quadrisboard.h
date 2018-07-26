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
#include "window.h"


using namespace std;

class Level;
class Block;
class Cell;
class Xwindow;

class QuadrisBoard {

    // Singleton design pattern
    static shared_ptr<QuadrisBoard>instance;
    QuadrisBoard(bool graphics = true);
    Xwindow *xw;

    vector<vector<shared_ptr<Cell>>> board;
    shared_ptr<Block> currentBlock;
    char nextBlock;
    shared_ptr<Level> level;

    vector<shared_ptr<Block>> blocksOnBoard;

    int score;
    int highScore;


public:
    ~QuadrisBoard();
    static shared_ptr<QuadrisBoard> getInstance(bool graphics = true);

    vector<vector<shared_ptr<Cell>>> getBoard();
    void setBoard(vector<vector<shared_ptr<Cell>>> newBoard);

    shared_ptr<Level> getLevel();
    void setLevels(shared_ptr<Level> newLevels);

    void setNextBlock(char block);

    shared_ptr<Block> getCurrentBlock();

    void initialize();
    bool isLost();
    void printText(bool seeInvisible = true, char empty = ' ');
    int getColour(char bType);
    void printGraphic(bool seeInvisible = true);
    void executeCommand(string name);
    bool isFullRow(int rowIndex);
    void clearRow(int rowIndex);
    void dropRowsAbove(int rowIndex);
    void dropTop(int rowIndex, int colIndex);
    bool isBlockStuck();
    bool isBlockStuck(shared_ptr<Block>);
    bool deleteCellFromBlock(shared_ptr<Block>, int, int);
    bool cellBelowIsSticky(shared_ptr<Block>, int, int);
    //Interpreter *patternMatchName(string name); //......add shared ptr

    void replaceBlock(string blockType);
    void addToScore(int newScore);
    void checkClearedBlocks();
    void setNextBlock();

    //~QuadrisBoard();
    void levelUp();
    void levelDown();
    void restart();
    void hint();
    void random();
    void norandom();
    bool validateCoord(vector<pair<int,int>> coordToCheck);
    void getNextBlock();
    void setLevel(shared_ptr<Level> level);
    void moveBlock(vector<pair<int,int>> coordToCheck);

    void setXW();
};

#endif
