#include "cell.h"
#include <vector>

class Block {
    char blockType;
    vector <Cell *> cells;
public:
    virtual move();
};


