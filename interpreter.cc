#include "interpreter.h"

bool isBlockName(string command) {
    if (command == "I" || command == "J" || command == "L" || command == "O" || command == "S" || command == "T" || command == "Z") return true;
    return false;
}

/// Change graphics display to be true by default after implementation ///

Interpreter::Interpreter() : graphicsDisplay{true}, seed{0},
                             scriptFile{"sequence.txt"}, startLevel{0} {}

void Interpreter::startGame() {
    cout<<"startGame()"<<endl;

    board = QuadrisBoard::getInstance();
    board->setLevel(startLevel);
    display = make_shared<Display>(graphicsDisplay, board);
    board->getNextBlock();

    string nextCommand;
    display->print(true, '-');   //TODO: display->print(false, ' ')

    while (cin >> nextCommand) {
        cout<<"Got command"<<endl;
        if(nextCommand.length() <= 1 && isBlockName(nextCommand)) {
            cout<<"Trying to replace block"<<endl;
            board->replaceBlock(nextCommand);
        }

        else {

            // implement multiplying commands feature

            string fullCommand = interpretCommand(nextCommand);

            if (fullCommand == "") {
                continue;
            }

            cout<<"Trying to execute command: "<<fullCommand<<endl;
            executeCommand(fullCommand);
            if(board->isBlockStuck()) {
                cout<<"Block is stuck"<<endl;
                if(board->isLost()) {
                    cout << "Game Over" <<endl;
                    display->print(true, '-');   //TODO: display->print(false, ' ')
                    return;
                }

                for(int i=0; i<HEIGHT; i++) {
                    if(board->isFullRow(i)) {
                        cout<<"Row "<<i<<" is full"<<endl;
                        board->clearRow(i);
                    }
                }
                board->getNextBlock();
            }
        }

        display->print(true, '-');   //TODO: display->print(false, ' ')
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
        board->getCurrentBlock()->left();
    } else if (nextCommand == "right") {
        board->getCurrentBlock()->right();
    } else if (nextCommand == "down") {
        board->getCurrentBlock()->down();
    } else if (nextCommand == "clockwise") {
        board->getCurrentBlock()->clockwise();
    } else if (nextCommand == "counterclockwise") { //counter
        board->getCurrentBlock()->counter();
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
    } else {
        // world explosion???????
        cerr << "Interpreter::executeCommand: command not found" <<endl;
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

void Interpreter::renameCommand() {

}


Interpreter::~Interpreter() {

}

