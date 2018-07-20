#ifndef QUADRISBOARD_H
#define QUADRISBOARD_H

#include <vector>
#include <string>
#include <iostream>
#include "cell.h"
#include "cinterpreter.h"
#include "level.h"
#include "constants.h"
#include "block.h"

using namespace std;

class Interpreter;
class Level;

class QuadrisBoard {

    vector<vector<Cell *>> board; //11x18
    vector<Block *> blocksOnBoard;
    int currentBlockIndex;
    //map<string, Command*> commandMap;
    Level* levels;
    int currentLevel;
    //Display display;

public:
    QuadrisBoard();

    vector<vector<Cell *>> getBoard();
    void setBoard(vector<vector<Cell *>> newBoard);
    vector<Block *> getBlocksOnBoard();
    void setBlocksOnBoard(vector<Block *> newBlocksOnBoard);
    int getCurrentBlockIndex();
    void setCurrentBlockIndex(int newCurrentBlockIndex);
    Level* getLevels();
    void setLevels(Level* newLevels);
    int getCurrentLevel();
    void setCurrentLevel(int newCurrentLevel);

    bool isLost();
    void print(bool seeInvisible = true);
    void executeCommand(string name);
    bool isFullRow(int rowIndex);
    void clearRow(int rowIndex);
    void dropRowsAbove(int rowIndex);
    void dropTop(int rowIndex, int colIndex);
    bool isBlockStuck(Block *);
    bool deleteCellFromBlock(Block*, int, int);
    bool cellBelowIsSticky(Block*, int, int);
    Interpreter *patternMatchName(string name);

    ~QuadrisBoard();

};

#endif
