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

    int level;
    bool heavy;

    std::string inputFile;
    std::ifstream fileIn;

public:

    // Constructor
    Level(int level, string input);

    // Getters and Setters
    int getLevel();
    void setLevel(int newLevel);
    bool getHeavy();
    void setHeavy(bool newHeavy);

    // Gets next block
    char getNextBlockType();

    // Destructor
    ~Level();

protected:
    char level0Block();
    char otherLevelBlock();
};

#endif
