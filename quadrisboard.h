#ifndef QUADRISBOARD_H
#define QUADRISBOARD_H

#include <vector>
#include "cell.h"
#include "cinterpreter.h"
#include "level.h"

using namespace std;

class QuadrisBoard {

    vector<vector<Cell *>> board;
    vector<Block *> blocksOnBoard;
    int currentBlockIndex;
    //map<string, Command*> commandMap;
    vector<Level> levels;
    int currentLevel;
    //Display display;

public:
    QuadrisBoard();

    bool isLost();
    void print();
    void executeCommand(string name);
    bool isFullRow(int rowIndex);
    void clearRow(int rowIndex);
    void dropRowsAbove(int rowIndex);
    bool isBlockStuck();
    Interpreter *patternMatchName(string name);

    ~QuadrisBoard();

};

#endif QUADRISBOARD_H
