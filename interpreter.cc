#include "interpreter.h"


/// Change graphics display to be true by default after implementation ///

Interpreter::Interpreter() : graphicsDisplay{false}, seed{0},
                             scriptFile{"sequence.txt"}, startLevel{0} {

    board = QuadrisBoard::getInstance();
}

void Interpreter::startGame() {

    string nextCommand;

    while (cin >> nextCommand) {

        if(nextCommand.length() <= 1) {
            // Is it a block name?
        }

        else {

            // implement multiplying commands feature

            string fullCommand = interpretCommand(nextCommand);

            if (fullCommand == "") {
                continue;
            }

            executeCommand(fullCommand);
        }
    }
}



string Interpreter::interpretCommand(string nextCommand) {

    vector<string> commands = COMMANDS;

    int possibilities = 0;
    string matchedCommand;

    for (int i = 0; i < commands.size(); ++i) {

        if(commands[i].compare(0, nextCommand.length(), nextCommand) == 0) {
            matchedCommand = commands[i];
            possibilities++;
        }
    }

    if (possibilities != 1) {
        if (possibilities == 0) {
            cerr << "Error: No command found matching that name" << endl;
        } else {
            cerr << "Error: Multiple commands exist with this name" << endl;
        }

        return "";
    }


    return matchedCommand;

}

void Interpreter::executeCommand(string nextCommand) {

    if (nextCommand == "left") {

    } else if (nextCommand == "right") {

    } else if (nextCommand == "down") {

    } else if (nextCommand == "clockwise") {

    } else if (nextCommand == "counterclockwise") {

    } else if (nextCommand == "drop") {

    } else if (nextCommand == "levelup") {

    } else if (nextCommand == "leveldown") {

    } else if (nextCommand == "restart") {

    } else if (nextCommand == "hint") {

    } else {

        // world explosion???????
    }
}


bool Interpreter::getGraphicsDisplay() {
    return graphicsDisplay;
}

void Interpreter::setGraphicsDisplay(bool graphics) {
    graphicsDisplay = graphics;
}

string Interpreter::getScriptFile() {
    return scriptFile;
}

void Interpreter::setScriptFile(string file) {
    scriptFile = file;
}

int Interpreter::getSeed() {
    return seed;
}

void Interpreter::setSeed(int newSeed) {
    seed = newSeed;
}

int Interpreter::getStartLevel() {
    return startLevel;
}

void Interpreter::setStartLevel(int level) {
    startLevel = level;
}


void Interpreter::action(QuadrisBoard *board, Block *block) {

}

bool Interpreter::isPossible(QuadrisBoard *board, Block *block, string command) {
    //TODO
}

void Interpreter::renameCommand() {

}


Interpreter::~Interpreter() {


}

