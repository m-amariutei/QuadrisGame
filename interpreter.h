#ifndef COMMAND_H
#define COMMAND_H

#define BLOCKS { 'I', 'J', 'L', 'O', 'S', 'T', 'Z' };

#include <string>
#include <memory>
#include "quadrisboard.h"

using namespace std;

class QuadrisBoard;

class Interpreter {


    shared_ptr<QuadrisBoard> board;
    string currentCommand;
    bool graphicsDisplay;
    string scriptFile;
    int seed;
    int startLevel;

public:
    Interpreter();
    void startGame();

    bool getGraphicsDisplay();
    void setGraphicsDisplay(bool graphics);

    string getScriptFile;
    void setScriptFile(string file);

    int getSeed();
    void setSeed(int seed);

    int getStartLevel();
    void setStartLevel(int level);

    void action(QuadrisBoard *board, Block *block);
    bool isPossible(QuadrisBoard *board, Block *block, string command);
    void renameCommand();

    ~Interpreter();

protected:
    string interpretCommand(string nextCommand);
    void executeCommand(string nextCommand);

};

#endif
