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


using namespace std;

class Level;
class Block;
class Cell;

class QuadrisBoard {

    // Singleton design pattern
    static shared_ptr<QuadrisBoard>instance;
    QuadrisBoard();


    vector<vector<shared_ptr<Cell>>> board;
    shared_ptr<Block> currentBlock;
    char nextBlock;
    shared_ptr<Level> level;

    vector<shared_ptr<Block>> blocksOnBoard;

    int score;
    int highScore;
    int dropsWithoutClear;

public:

    static shared_ptr<QuadrisBoard> getInstance();

    vector<vector<shared_ptr<Cell>>> getBoard();
    void setBoard(vector<vector<shared_ptr<Cell>>> newBoard);

    shared_ptr<Level> getLevel();
    void setLevels(shared_ptr<Level> newLevels);

    void setNextBlock(char block);

    shared_ptr<Block> getCurrentBlock();

    void initialize();
    bool isLost();
    void print(bool seeInvisible = true, char empty = ' ');
    bool isFullRow(int rowIndex);
    void clearRow(int rowIndex);
    void dropRowsAbove(int rowIndex);
    void dropTop(int rowIndex, int colIndex);
    bool isBlockStuck();
    bool isBlockStuck(shared_ptr<Block>);
    bool deleteCellFromBlock(shared_ptr<Block>, int, int);
    bool cellBelowIsSticky(shared_ptr<Block>, int, int);

    void addToScore(int newScore);
    void checkClearedBlocks();
    bool replaceBlock(string blockType);
    void setNextBlock();

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
};

#endif
