#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include "quadrisboard.h"

using namespace std;

class QuadrisBoard;

class Interpreter {

    string currentCommand;

public:
    Interpreter(std::istream &i, bool textOnly, int seed);

    void action(QuadrisBoard *board, Block *block);
    bool isPossible(QuadrisBoard *board, Block *block, string command);
    void renameCommand();

    ~Interpreter();

};

#endif
