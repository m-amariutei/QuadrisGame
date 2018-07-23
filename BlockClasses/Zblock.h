//
// Created by Dasha Burmistrova on 2018-07-19.
//

#ifndef GITHUB_ZBLOCK_H
#define GITHUB_ZBLOCK_H

#include "../block.h"
#include <vector>

class Zblock: public Block {
public:
    Zblock();

    void clockwise() override;

    void counter() override;

};

#endif //GITHUB_ZBLOCK_H
