#include "block.h"

Block::Block(vector<shared_ptr<Cell>> cells, char type, int level): cells{cells}, type{type}, levelInitialized{level} {
    board = QuadrisBoard::getInstance();
}

vector<shared_ptr<Cell>> Block::getCells() { return cells; }

void Block::setCells(vector<shared_ptr<Cell>> newCells) { cells = newCells; }

int Block::getLevelInitialized() { return levelInitialized; }
void Block::setLevelInitialized(int level) { levelInitialized = level; }

char Block::getType() { return type; }

void Block::setType(char newType) { type = newType; }

bool Block::right() {
    //create coords
    vector<pair<int,int>> coords;
    for(int i=0; i<cells.size(); i++) {
        coords.push_back(make_pair(cells.at(i)->getYValue(), cells.at(i)->getXValue() + 1));       //row, col
    }
    
    //validate coords
    bool isValid = board->validateCoord(coords);

    //move block to coords
    if(isValid) {
        board->moveBlock(coords);
        return true;
    } else return false;
}

bool Block::left() {
     //create coords
    vector<pair<int,int>> coords;
    for(int i=0; i<cells.size(); i++) {
        coords.push_back(make_pair(cells.at(i)->getYValue(), cells.at(i)->getXValue() - 1));       //row, col
    }
    
    //validate coords
    bool isValid = board->validateCoord(coords);

    //move block to coords
    if(isValid) {
        board->moveBlock(coords);
        return true;
    } else return false;
}

bool Block::down() {
    //should always work (if not, generate new block)

    //create coords
    vector<pair<int,int>> coords;
    for(int i=0; i<cells.size(); i++) {
        coords.push_back(make_pair(cells.at(i)->getYValue() + 1, cells.at(i)->getXValue()));       //row, col
    }
    
    //validate coords
    bool isValid = board->validateCoord(coords);

    //move block to coords
    if(isValid) {
        board->moveBlock(coords);
        return true;
    }
    else {
        return false;
    }
}

void Block::drop() {
    //should always work (if not, generate new block)
    while(down());
    
}

bool Block::rotate(vector<int> values) {
    vector<pair<int,int>> coords;
    for (int i=0; i<cells.size(); i++) {
        int xVal = cells.at(i)->getXValue();
        int yVal = cells.at(i)->getYValue();
        pair<int,int> newCoord = make_pair(xVal - values[0] + values[1], values[2] + values[3] - yVal);
        coords.push_back(newCoord);
        // cout<<"("<<xVal<<","<<yVal<<") -> (" << coords.at(i).first << "," << coords.at(i).second <<")"<<endl;
    }

    bool isValid = board->validateCoord(coords);

    if(isValid) {
        board->moveBlock(coords);
        return true;
    }
    else {
        return false;
    }
}

pair<int,int> Block::getMinMaxElements(bool isX) {
    if(isX) {
        vector<int> xs;
        for (int i=0; i<cells.size(); i++) {
            xs.push_back(cells.at(i)->getXValue());
        }
        auto result =  minmax_element(xs.begin(), xs.end());
        return make_pair(*result.first,*result.second);
    } else {
        vector<int> ys;
        for (int i=0; i<cells.size(); i++) {
            ys.push_back(cells.at(i)->getYValue());
        }
        auto result = minmax_element(ys.begin(), ys.end());
        return make_pair(*result.first,*result.second);
    }
}

bool Block::clockwise() {
    pair<int,int> Xs = getMinMaxElements(true);
    pair<int,int> Ys = getMinMaxElements(false);

    vector<int> values;
    values.push_back(Xs.first+1);
    values.push_back(Ys.second);
    values.push_back(Xs.second-1);
    values.push_back(Ys.second);
    return rotate(values);
}

bool Block::counter() {
    pair<int,int> Xs = getMinMaxElements(true);
    pair<int,int> Ys = getMinMaxElements(false);

    vector<int> values;
    values.push_back(Xs.first);
    values.push_back(Ys.first);
    values.push_back(Xs.first);
    values.push_back(Ys.second);
    return rotate(values);
}

bool Block::hasNoCells() {

    return cells.empty();
}
