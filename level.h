
#ifndef LEVEL_H
#define LEVEL_H

#include <string>
#include <fstream>
#include "quadrisboard.h"

class Level {

    int level;
    bool heavy;

    std::string inputFile;
    std::ifstream fileIn;

public:

    // Constructor
    Level(int level);

    // Getters and Setters
    int getLevel();
    void setLevel(int level);
    bool getHeavy();
    void setHeavy(bool heavy);

    // Gets next block
    char getNextBlockType();

    // Destructor
    ~Level();

protected:
    char level0Block();
    char otherLevelBlock();
};

#endif
