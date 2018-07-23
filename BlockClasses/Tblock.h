//
// Created by Dasha Burmistrova on 2018-07-19.
//

#ifndef GITHUB_TBLOCK_H
#define GITHUB_TBLOCK_H

#include "../block.h"
#include <vector>

class Hblock: public Block {
public:
    Hblock();

    void clockwise() override;

    void counter() override;

};

#endif //GITHUB_TBLOCK_H
