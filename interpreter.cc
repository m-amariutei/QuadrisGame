#include <sstream>
#include "interpreter.h"

bool isMove(string s) {
    if(s == "left" || s == "right" || s == "down" || s == "clockwise" || s == "counterclockwise" || s == "drop") return true;
    else return false;
}

bool isBlockName(string command) {
    if (command == "I" || command == "J" || command == "L" || command == "O" || command == "S" || command == "T" || command == "Z") return true;
    return false;
}

/// Change graphics display to be true by default after implementation ///

Interpreter::Interpreter() : graphicsDisplay{true}, seed{0},
                             scriptFile{"sequence.txt"}, startLevel{0} {}

void Interpreter::startGame() {

    cout << "startGame()" << endl;

    board = QuadrisBoard::getInstance();

    shared_ptr<Level> level = Level::getInstance(startLevel, scriptFile);
    level->setSeed(seed);
    level->setDropsWithoutClear(0);
    board->setLevel(level);

    board->setNextBlock();

    display = make_shared<Display>(graphicsDisplay, board);

    board->getNextBlock();
    board->getCurrentBlock()->down();
    board->getCurrentBlock()->down();
    if(board->getCurrentBlock()->getType() != 'T' &&
        board->getCurrentBlock()->getType() != 'S') {
        board->getCurrentBlock()->down();
    }

    string nextCommand;
    display->print(true, '-');   //TODO: display->print(false, ' ')

    while (cin >> nextCommand) {

        int multiplier = 1;

        if (47 < nextCommand[0] && nextCommand[0] < 58) {

            string number = "";
            int i = 0;

            // Get multiplier number from command line
            // Takes into account if it is multiple digits
            while (47 < nextCommand[i] && nextCommand[i] < 58) {
                number += nextCommand[i];
                i++;
            }

            // Make string an int
            stringstream(number) >> multiplier;

            // Remove numbers from command before trying to interpret
            int totalLen = nextCommand.length();
            nextCommand = nextCommand.substr(i, totalLen);
        }

        if (nextCommand.length() <= 1 && isBlockName(nextCommand)) {

            cout<<"Trying to replace block"<<endl;
            bool replace = board->replaceBlock(nextCommand);
            //don't drop
        }

        else {

            // implement multiplying commands feature

            string fullCommand = interpretCommand(nextCommand);

            if (fullCommand == "") {
                continue;
            }

            if (fullCommand == "norandom") {
                string newScriptFile;
                cin >> newScriptFile;
                setScriptFile(newScriptFile);
                level->setRandom(false);
                level->setInputFile(newScriptFile);
            }

            if (fullCommand == "random") {
                level->setRandom(true);
            }

            while (multiplier > 0) {

                bool successMove = executeCommand(fullCommand);
                if (successMove && isMove(fullCommand) && board->getLevel()->getHeavy()) {
                    executeCommand("down");
                }

                if (fullCommand == "drop" || !isMove(fullCommand)) {multiplier = 0;}

                if(!board->getCurrentBlock()) {
                    board->getNextBlock();
                    board->getCurrentBlock()->down();
                    board->getCurrentBlock()->down();
                    if(board->getCurrentBlock()->getType() != 'T' &&
                        board->getCurrentBlock()->getType() != 'S') {
                        board->getCurrentBlock()->down();
                    }
                    if (checkIfLost()) {
                        return;
                    }
                }

                if (board->isBlockStuck()) {

                    if (board->isLost()) {
                        display->print(true, '-');   //TODO: display->print(false, ' ')

                        cout << "Game Over" << endl;
                        cout << "You have lost, please play again!" << endl;

                        return;
                    }

                    int cleared = 0;
                    int drops = level->getDropsWithoutClear();

                    for (int i = 0; i < HEIGHT; i++) {
                        if (board->isFullRow(i)) {
                            //cout << "Row " << i << " is full" << endl;
                            board->clearRow(i);
                            cleared++;
                        }
                    }
                    int newPoints = ((level->getLevel() * cleared) * (level->getLevel() * cleared));
                    board->addToScore(newPoints);

                    if (cleared > 0) {
                        board->checkClearedBlocks();
                        level->setDropsWithoutClear(0);
                    } else {
                        level->setDropsWithoutClear(++drops);
                    }

                    board->getNextBlock();
                    board->getCurrentBlock()->down();
                    board->getCurrentBlock()->down();
                    if(board->getCurrentBlock()->getType() != 'T' &&
                        board->getCurrentBlock()->getType() != 'S') {
                        board->getCurrentBlock()->down();
                    }
                    if (checkIfLost()) {
                        return;
                    }
                }

                multiplier--;
            }
        }

        display->print(true, '-');   //TODO: display->print(false, ' ')
    }
}

bool Interpreter::checkIfLost() {
    if(board->isLost()) {
        cout << "Game Over" <<endl;
        display->print(true, '-');   //TODO: display->print(false, ' ')
        return true;
    }
    return false;
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

bool Interpreter::executeCommand(string nextCommand) {
    bool successMove = true;
    if (nextCommand == "left") {
        successMove = board->getCurrentBlock()->left();
    } else if (nextCommand == "right") {
        successMove = board->getCurrentBlock()->right();
    } else if (nextCommand == "down") {
        board->getCurrentBlock()->down();
    } else if (nextCommand == "clockwise") {
        successMove = board->getCurrentBlock()->clockwise();
    } else if (nextCommand == "counterclockwise") { //counter
        successMove = board->getCurrentBlock()->counter();
    } else if (nextCommand == "drop") {
        board->getCurrentBlock()->drop();
    } else if (nextCommand == "levelup") {
        board->levelUp();
    } else if (nextCommand == "leveldown") {
        board->levelDown();
    } else if (nextCommand == "restart") {
        board->restart();
    } else if (nextCommand == "hint") {
        board->hint();
    } else if (nextCommand == "random") {
        board->setNextBlock();
    } else if (nextCommand == "norandom") {
        board->setNextBlock();
    } else {
        // world explosion???????
        cerr << "Interpreter::executeCommand: command not found" <<endl;
        successMove = false;
    }
    return successMove;
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

Interpreter::~Interpreter() {

}

