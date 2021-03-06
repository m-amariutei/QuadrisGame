#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <iostream>
#include <memory>
#include "quadrisboard.h"
#include "level.h"
#include "constants.h"
#include "display.h"

using namespace std;

class Display;
class QuadrisBoard;

class Interpreter {

    shared_ptr<Display> display;
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

    string getScriptFile();
    void setScriptFile(string file);

    int getSeed();
    void setSeed(int seed);

    int getStartLevel();
    void setStartLevel(int level);


    ~Interpreter();

protected:
    string interpretCommand(string nextCommand);
    bool executeCommand(string nextCommand);
    bool checkIfLost();
};

#endif
