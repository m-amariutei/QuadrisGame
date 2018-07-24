
#include <string>
#include <iostream>
#include <sstream>
#include "interpreter.h"

int main(int argc, char *argv[]) {

    Interpreter* gameInterpreter = new Interpreter();

    for (int i = 0; i < argc; i++) {

        string spec = argv[i];

        if (spec == "-text") {

            gameInterpreter->setGraphicsDisplay(false);
        } else if (spec == "-seed") {

            int seed;
            stringstream(argv[++i]) >> seed;

            gameInterpreter->setSeed(seed);
        } else if (spec == "-scriptfile") {

            gameInterpreter->setScriptFile(string(argv[++i]));
        } else if (spec == "-startlevel") {

            int level;
            stringstream(argv[++i]) >> level;

            gameInterpreter->setStartLevel(level);
        } else {

            /// EXCEPTION HERE ///
        }
    }

    gameInterpreter->startGame();

    delete gameInterpreter;

}