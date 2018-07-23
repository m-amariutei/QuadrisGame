//
// Created by Dasha Burmistrova on 2018-07-18.
//

#ifndef GITHUB_OBLOCK_H
#define GITHUB_OBLOCK_H

#include "../block.h"
#include <vector>

class Oblock: public Block {
public:
    Oblock();

    void move();

    void clockwise() override;

    void counter() override;

};

#endif //GITHUB_OBLOCK_H
