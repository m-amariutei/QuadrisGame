//
// Created by Dasha Burmistrova on 2018-07-18.
//

#ifndef GITHUB_JBLOCK_H
#define GITHUB_JBLOCK_H

#include "../block.h"
#include <vector>

class Jblock: public Block {
public:
    Jblock();

    void clockwise() override;

    void counter() override;

};

#endif //GITHUB_JBLOCK_H
