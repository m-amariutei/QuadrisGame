//
// Created by Dasha Burmistrova on 2018-07-18.
//

#ifndef GITHUB_SBLOCK_H
#define GITHUB_SBLOCK_H

#include "../block.h"
#include <vector>

class Sblock: public Block {
public:
    Sblock();

    void clockwise() override;

    void counter() override;

};

#endif //GITHUB_SBLOCK_H
