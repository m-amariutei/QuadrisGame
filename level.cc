#include <iostream>
#include <ctime>
#include "level.h"

using namespace std;

shared_ptr<Level> Level::instance = 0;

shared_ptr<Level> Level::getInstance(int level, string input) {
    if (instance == 0) {
        static shared_ptr<Level> newLevel(new Level(level, input));
        instance = newLevel;
    }
    return instance;

}

Level::Level(int level, string input) : level{level}, inputFile{input} {

    if (!fileIn.is_open()) {
        fileIn.open(inputFile.c_str());
    }
    if(level >= 3) heavy = true;
    else heavy = false;
}

char Level::getNextBlockType() {

    if (level == 0 || ((level == 3 || level == 4) && random == false)) {

        char block;

        if (fileIn >> block) {
            return block;
        } else {
            fileIn.close();
            return '0';

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

    //srand(time( NULL ));

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

bool Level::getRandom() { return random; }
void Level::setRandom(bool randomness) { random = randomness; }

void Level::setSeed(int newSeed) { seed = newSeed; }

int Level::getDropsWithoutClear() {
    return dropsWithoutClear;
}
void Level::setDropsWithoutClear(int drops) {
    dropsWithoutClear = drops;
}

string Level::getInputFile() {return inputFile; }

void Level::setInputFile(string input) {
    inputFile = input;
    if (fileIn.is_open()) {
        fileIn.close();
    }
    fileIn.open(inputFile.c_str());
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

