#include <iostream>
#include "level.h"

using namespace std;

// Level Probabilities
#define LEVEL1 { 2, 2, 2, 2, 1, 2, 1 };
#define LEVEL2 { 1, 1, 1, 1, 1, 1, 1 };
#define LEVEL3 { 1, 1, 1, 1, 2, 1, 2 };
// Block Identifiers
#define BLOCKS { 'I', 'J', 'L', 'O', 'S', 'T', 'Z' };

Level::Level(int level) : level{level} {

    fileIn.open(inputFile.c_str());
}

char Level::getNextBlockType() {

    if (level == 0) {

        char block;

        if (fileIn >> block) {
            return block;
        } else {
            fileIn.close();
            return 'D'; //Input file is done
        }

        /// Check for invalid block type ///
    }
    else {return otherLevelBlock();}

}


char Level::otherLevelBlock() {

    int max;
    vector<int> probabilities;
    vector<char> blocks = BLOCKS;

    if (level == 1) {
        max = 12;
        probabilities = LEVEL1;
    }
    else if (level == 2) {
        max = 7;
        probabilities = LEVEL2;
    }
    else  {
        max = 9;
        probabilities = LEVEL3;
    }

    int random = rand() % max;
    max--;

    for (int i = 0; i < 7; i++) {

        max = max - probabilities[i];

        if (random >= max) {
            return blocks[i];
        }
    }
}


Level::~Level() {

    fileIn.close();
}