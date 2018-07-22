#include "block.h"
#include <vector>

Block::Block() {} /// TO DO ///

vector<Cell*> Block::getCells() { return cells; }

char Block::getType() { return type; }

/// TO DO ///
void Block::move(vector<Cell*> newLocation) {

}

/// TO DO ///
bool Block::validate(vector<Cell*> newLocation) {

    return true;
}

Block::~Block() {}
