
#ifndef LEVEL_H
#define LEVEL_H

#include "quadrisboard.h"

class Level {

    QuadrisBoard *board;
    string levelName;
    bool heavy;

public:
    Level();

    Block* createNextBlock();

    ~Level();

};

#endif
