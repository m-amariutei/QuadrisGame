#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <memory>
#include <string>
#include <fstream>
#include <vector>
#include "constants.h"

using namespace std;

class Level {

    static shared_ptr<Level> instance;
    Level();
    // Constructor
    Level(int level, string input);

    int level;
    bool random = true;
    bool heavy;
    int seed;

    std::string inputFile;
    std::ifstream fileIn;
    int dropsWithoutClear;

public:

    static shared_ptr<Level> getInstance(int level, string input);
    // Getters and Setters
    int getLevel();
    void setLevel(int newLevel);
    bool getRandom();
    void setRandom(bool randomness);
    void setSeed(int newSeed);
    int getDropsWithoutClear();
    void setDropsWithoutClear(int drops);
    string getInputFile();
    void setInputFile(string input);
    bool getHeavy();
    void setHeavy(bool newHeavy);

    // Gets next block
    char getNextBlockType();

    // Destructor
    ~Level();

protected:
    char otherLevelBlock();
};

#endif
