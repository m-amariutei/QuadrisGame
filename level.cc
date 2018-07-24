#include <iostream>
#include "level.h"

using namespace std;

Level::Level(int level) : level{level} {

    fileIn.open(inputFile.c_str());
    if(level >= 3) heavy = true;
    else heavy = false;
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

    return blocks[0];
}

int Level::getLevel() {
    return level;
}

void Level::setLevel(int newLevel) {
    level = newLevel;
    if(level >=3) heavy = true;
    else heavy = false;
}

bool Level::getHeavy() {
    return heavy;
}

void Level::setHeavy(bool newHeavy) {
    heavy = newHeavy;
}


Level::~Level() {

    fileIn.close();
}

