//
// Created by Dasha Burmistrova on 2018-07-18.
//

#ifndef GITHUB_LBLOCK_H
#define GITHUB_LBLOCK_H

#include "../block.h"
#include <vector>

class Lblock: public Block {
public:
    Lblock();

    void clockwise() override;

    void counter() override;

};

#endif //GITHUB_LBLOCK_H
