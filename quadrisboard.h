#ifndef QUADRISBOARD_H
#define QUADRISBOARD_H

#include <vector>
#include <string>
#include <iostream>
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

    vector<vector<Cell *>> board; //11x18
    vector<Block *> blocksOnBoard;
    int currentBlockIndex;
    Level* level;
    bool graphicDisplay;
    Display display;



public:

    static shared_ptr<QuadrisBoard> getInstance();

    vector<vector<Cell *>> getBoard();
    void setBoard(vector<vector<Cell *>> newBoard);

    vector<Block *> getBlocksOnBoard();
    void setBlocksOnBoard(vector<Block *> newBlocksOnBoard);

    int getCurrentBlockIndex();
    void setCurrentBlockIndex(int newCurrentBlockIndex);

    Level* getLevels();
    void setLevels(Level* newLevels);


    void initialize();
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
