//
// Created by Dasha Burmistrova on 2018-07-18.
//

#ifndef GITHUB_IBLOCK_H
#define GITHUB_IBLOCK_H

#include "../block.h"
#include <vector>

class Iblock: public Block {
public:
    Iblock(vector<shared_ptr<Cell>> cells, char type);
    void clockwise() override;

    void counter() override;

};

#endif //GITHUB_IBLOCK_H
