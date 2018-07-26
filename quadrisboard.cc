#include "quadrisboard.h"

shared_ptr<QuadrisBoard> QuadrisBoard::instance = 0;

shared_ptr<QuadrisBoard> QuadrisBoard::getInstance() {

	if (instance == 0) {
		static shared_ptr<QuadrisBoard> newBoard(new QuadrisBoard);
		instance = newBoard;
	}
	return instance;

}

void printCoords(vector<pair<int,int>> coords) {
	cout<<"Printing coords"<<endl;
	for(int i=0; i<coords.size(); i++) {
		cout<<"("<<coords.at(i).first<<","<<coords.at(i).second<<")"<<endl;
	}
}

QuadrisBoard::QuadrisBoard() {
	initialize();
}

void QuadrisBoard::initialize() {

	for (int i = 0; i < HEIGHT; i++) {

		vector<shared_ptr<Cell>> row;
		board.push_back(row);

		for (int j = 0; j < WIDTH; j++) {

			shared_ptr<Cell> cell = make_shared<Cell>(j,i, nullptr);
			board.at(i).push_back(cell);
		}
	}

	currentBlock = nullptr;	//no blocks
	nextBlock = ' ';
	score = 0;
	highScore = 0;
}

void QuadrisBoard::checkClearedBlocks() {

	for (int i = 0; i < blocksOnBoard.size(); i++) {
		if (blocksOnBoard[i]->hasNoCells()) {

			int levelPoints = blocksOnBoard[i]->getLevelInitialized() + 1;
			levelPoints = levelPoints * levelPoints;

			addToScore(levelPoints);

			blocksOnBoard.erase(blocksOnBoard.begin() + i);
			i--;
		}

	}
}

void QuadrisBoard::setNextBlock() {
	nextBlock = level->getNextBlockType();
}

bool QuadrisBoard::isLost() {

	for (int i = 0; i < WIDTH; i++) {

		if(board.at(LOST_ROW).at(i)->getBlock() != nullptr && board.at(LOST_ROW).at(i)->getBlock() != currentBlock )  {
			return true;
		} else if (board.at(LOST_ROW).at(i)->getBlock() != nullptr && board.at(LOST_ROW).at(i)->getBlock() == currentBlock && isBlockStuck()) {
			return true;
		}
	}

	return false;
}

void QuadrisBoard::print(bool seeInvisible, char empty) {

	cout << "Level:         " << level->getLevel() << endl;
	cout << "Score:         " << score << endl;
	cout << "High Score:      " << highScore << endl;
	cout << "----------------" << endl;

	int begRow = NUM_ROWS_INVISIBLE;
	if(seeInvisible) begRow = 0;

	for (int i = begRow; i < HEIGHT; i++) {

		for(int j = 0; j < WIDTH; j++) {

			auto block = board.at(i).at(j)->getBlock();

			if(block != nullptr) {
				cout<< block->getType();
			} else {
				cout<<empty;
			}
			
		}
		cout<<endl;
		if(i==NUM_ROWS_INVISIBLE-1) cout << "++++++++++++++++" << endl;
	}

	cout << "----------------" << endl;
	cout << "Next Block: " << nextBlock << endl;
	//print next piece coming
}

bool QuadrisBoard::isFullRow(int rowIndex) {

	if (rowIndex >= HEIGHT) cerr << "QuadrisBoard::isFullRow: rowIndex >= HEIGHT" <<endl;

	for (int i = 0; i < WIDTH; i++) {
		if (board.at(rowIndex).at(i)->getBlock() == nullptr) return false;
	}
	return true;
}

bool QuadrisBoard::deleteCellFromBlock(shared_ptr<Block> block, int x, int y) {

	for (vector<shared_ptr<Cell>>::const_iterator it = block->getCells().begin(); it != block->getCells().end(); it++) {

		if ((*it)->getXValue() == x && (*it)->getYValue() == y) {

			block->getCells().erase(it);
			return true;
		}
	}

	return false;
}

void QuadrisBoard::clearRow(int rowIndex) {

	if (rowIndex >= HEIGHT) cerr << "QuadrisBoard::clearRow: rowIndex >= HEIGHT" <<endl;

	if (!isFullRow(rowIndex)) cerr << "Quadrisboard.cc/clearRow: called on non-full row" <<endl;

	for (int i = 0; i < WIDTH; i++) {
		//let both cell and block know about this
		shared_ptr<Cell> cell = board.at(rowIndex).at(i);
		shared_ptr<Block> block = cell->getBlock();
		if (block == nullptr) cerr << "quadrisboard.cc/clearRow: block should not be NULL here" <<endl;

		cell->setBlock(nullptr);
		bool wasDeletedSuccessfully = false;
		wasDeletedSuccessfully = deleteCellFromBlock(block, cell->getXValue(), cell->getYValue());
		if (!wasDeletedSuccessfully)
			cerr << "quadrisboard.cc/clearRow: we deleted row " << rowIndex << "but failed to clear block->cells.at(" << i << ")" <<endl;
	}

	dropsWithoutClear = 0;
	dropRowsAbove(rowIndex);
}

void QuadrisBoard::dropRowsAbove(int rowIndex) {

	if (rowIndex >= HEIGHT || rowIndex <= 0) {
		return;
	}

	for (int i = rowIndex; i>LOST_ROW; i--) {
		for (int j=0; j<WIDTH; j++) {
			dropTop(i, j);
		}
	}
}

void QuadrisBoard::dropTop(int rowIndex, int colIndex) {
	if (rowIndex >= HEIGHT || rowIndex < LOST_ROW) {
		cerr << "QuadrisBoard::dropTop: rowIndex is wrong" <<endl;
	}

	if (colIndex >= WIDTH || colIndex < 0) {
		cerr << "QuadrisBoard::dropTop: colIndex is wrong" <<endl;
	}

	//take care of both cell and block class
	shared_ptr<Cell> cellDown = board.at(rowIndex).at(colIndex);

	//shared_ptr<Block> blockDown = cell->block;
	shared_ptr<Cell> cellTop = board.at(rowIndex - 1).at(colIndex);
	shared_ptr<Block> blockTop = cellTop->getBlock();

	if(rowIndex >= 16 && blockTop != nullptr) cout<<blockTop->getType()<<endl;

	cellDown->setBlock(blockTop);
	cellTop->setBlock(nullptr);
	//find Cell* in block that is above and replace it with a Cell* of the cell below
	if(blockTop != nullptr) blockTop->getCells().push_back(cellDown);
	
}

bool QuadrisBoard::isBlockStuck() {
	return isBlockStuck(currentBlock);
}

bool QuadrisBoard::isBlockStuck(shared_ptr<Block> block) {

	//return true iff below any cell occupied by this block, there is a cell occupied by another block or board ends
	for (int i = 0; i<block->getCells().size(); i++) {
		if (cellBelowIsSticky(block, block->getCells().at(i)->getXValue(), block->getCells().at(i)->getYValue())) return true;
	}
	return false;
}

bool QuadrisBoard::cellBelowIsSticky(shared_ptr<Block> block, int x, int y) {

	//Y is ROW and X is col
	if (y == HEIGHT - 1) return true;	//end of board reached

	else {
		shared_ptr<Cell> cellBelow = board.at(y+1).at(x);
		if (cellBelow->getBlock() != nullptr && cellBelow->getBlock() != block) return true;
		else return false;
	}
}

void QuadrisBoard::levelUp() {

    int levelInt = level->getLevel();
    if(levelInt > LEVEL_MAX) {
        cerr << "Level setting is wrong. Level is too high." << endl;
        return;
    } else if (levelInt == LEVEL_MAX) {
        return;
    } else {
        levelInt++;
        level->setLevel(levelInt);
        if(levelInt == 3 || levelInt == 4) {
            level->setHeavy(true);
        }
    }
}

void QuadrisBoard::levelDown() {

    int levelInt = level->getLevel();
    if(levelInt < LEVEL_MIN) {
        cerr << "Level setting is wrong. Level is too low." << endl;
        return;
    } else if (levelInt == LEVEL_MIN) {
        return;
    } else {
        levelInt--;
        level->setLevel(levelInt);
        if(levelInt == 0 || levelInt == 1 || levelInt == 2) {
            level-> setHeavy(false);
        }
    }
}

void QuadrisBoard::restart() {

    //wipe cells content
    for(int i=0; i<HEIGHT; i++) {
        for(int j=0; j<WIDTH; j++) {

            shared_ptr<Cell> cell = board.at(i).at(j);
            shared_ptr<Block> block = cell->getBlock();

            if(block != nullptr) {
                cell->setBlock(nullptr);
            }
        }
    }

    //wipe blocks not needed since they are smart pointers

    //wipe board content
    currentBlock = nullptr;
    score = 0;
    level->setDropsWithoutClear(0);
    nextBlock = level->getNextBlockType();
}

void QuadrisBoard::hint() {
    //TODO
}

bool QuadrisBoard::validateCoord(vector<pair<int,int>> coordToCheck) {	//row,col

	for(int i=0; i<coordToCheck.size(); i++) {

		if(coordToCheck.at(i).first < 0 || coordToCheck.at(i).first >= HEIGHT ||
			coordToCheck.at(i).second < 0 || coordToCheck.at(i).second >= WIDTH ||
			(board.at(coordToCheck.at(i).first).at(coordToCheck.at(i).second)->getBlock() != nullptr) &&
			board.at(coordToCheck.at(i).first).at(coordToCheck.at(i).second)->getBlock() != currentBlock) {
			return false;
		}
	}
	return true;
}

bool QuadrisBoard::replaceBlock(string blockType) {
	char newType = blockType.at(0);
	if(currentBlock->getType() == newType) return false;

	cout<<"FIniding leftLow"<<endl;
	pair<int,int> leftLow = make_pair(0,0);	//row, col
	for(int i=0; i<currentBlock->getCells().size(); i++) {
		int row = currentBlock->getCells().at(i)->getYValue();
		int col = currentBlock->getCells().at(i)->getXValue();
		cout<<"row,col: "<<row<<","<<col<<endl;
		if(row >= leftLow.first) {
			if(col <= leftLow.second) {
				leftLow = make_pair(row,col);
			}
		} 
		if (row > leftLow.first) {
			leftLow = make_pair(row,col);
		}

		//currentBlock->getCells().at(i)->setBlock(nullptr);
	}

	cout<<leftLow.first<<","<<leftLow.second<<endl;

	vector<pair<int,int>> coords;	//row, col
	int row, col;
	row = leftLow.first;
	col = leftLow.second;
	coords.push_back(make_pair(row, col));

	if(newType == 'I') {
		coords.push_back(make_pair(row-1, col));
		coords.push_back(make_pair(row-2, col));
		coords.push_back(make_pair(row-3, col));
	} else if(newType == 'J') {
		coords.push_back(make_pair(row, col+1));
		coords.push_back(make_pair(row-1, col+1));
		coords.push_back(make_pair(row-2, col+1));
	} else if(newType == 'L') {
		coords.push_back(make_pair(row-1, col));
		coords.push_back(make_pair(row-2, col));
		coords.push_back(make_pair(row, col+1));
	} else if(newType == 'O') {
		coords.push_back(make_pair(row-1, col));
		coords.push_back(make_pair(row, col+1));
		coords.push_back(make_pair(row-1, col+1));
	} else if(newType == 'S') {
		coords.push_back(make_pair(row, col+1));
		coords.push_back(make_pair(row-1, col+1));
		coords.push_back(make_pair(row-1, col+2));
	} else if(newType == 'T') {
		coords.push_back(make_pair(row-1, col-1));
		coords.push_back(make_pair(row-1, col));
		coords.push_back(make_pair(row-1, col+1));
	} else if(newType == 'Z') {
		coords.push_back(make_pair(row, col+1));
		coords.push_back(make_pair(row-1, col));
		coords.push_back(make_pair(row-1, col-1));
	} else {
		cerr << "replaceBlock with invalid type " << newType <<endl;
		return false;
	}

	printCoords(coords);

	if (validateCoord(coords)) {
		cout<<"Coords are OK"<<endl;
		vector<shared_ptr<Cell>> cellsForBlock;
		for(int i=0; i<coords.size(); i++) {
			cellsForBlock.push_back(board.at(coords.at(i).first).at(coords.at(i).second));
		}
		for(int i=0; i<currentBlock->getCells().size(); i++) {
			currentBlock->getCells().at(i)->setBlock(nullptr);
		}
		currentBlock = make_shared<Block>(cellsForBlock, newType, level->getLevel());
		for(int i=0; i<coords.size(); i++) {
			board.at(coords.at(i).first).at(coords.at(i).second)->setBlock(currentBlock);
		}
		return true;
	}
	return false;
}

 void QuadrisBoard::addToScore(int newScore) {
	score += newScore;

	if (score > highScore) highScore = score;
}

void QuadrisBoard::getNextBlock() {

	int dropsNoClear = level->getDropsWithoutClear();

	if(level->getLevel() == 4 && dropsNoClear > 0 && dropsNoClear % 5 == 0) {

		vector<shared_ptr<Cell>> cells;
		cells.push_back(board.at(0).at(5));
		shared_ptr<Block> starBlock = make_shared<Block>(cells,'*',level->getLevel());
		board.at(0).at(5)->setBlock(starBlock);
		//drop it
		currentBlock = starBlock;
		starBlock->drop();
	}

    char type = nextBlock;
    char nextType;

    nextType = level->getNextBlockType();

        if (nextType == '0') {
            print(true, '-');
            cout << "You have reached the end of the script file! Play at level 1 for more pieces" << endl;
            exit(0);
        }

	vector<shared_ptr<Cell>> cellsForBlock;

	nextBlock = nextType;

	// Initialize sells
    if(type == 'I') {
        cellsForBlock.push_back(board.at(0).at(0));
        cellsForBlock.push_back(board.at(1).at(0));
        cellsForBlock.push_back(board.at(2).at(0));
        cellsForBlock.push_back(board.at(3).at(0));

        currentBlock = make_shared<Block>(cellsForBlock, type, level->getLevel());

        board.at(0).at(0)->setBlock(currentBlock);
        board.at(1).at(0)->setBlock(currentBlock);
        board.at(2).at(0)->setBlock(currentBlock);
        board.at(3).at(0)->setBlock(currentBlock);
    } else if (type == 'J') {
    	cellsForBlock.push_back(board.at(0).at(1));
        cellsForBlock.push_back(board.at(1).at(1));
        cellsForBlock.push_back(board.at(2).at(1));
        cellsForBlock.push_back(board.at(2).at(0));

    	currentBlock = make_shared<Block>(cellsForBlock, type, level->getLevel());

    	board.at(0).at(1)->setBlock(currentBlock);
    	board.at(1).at(1)->setBlock(currentBlock);
    	board.at(2).at(1)->setBlock(currentBlock);
    	board.at(2).at(0)->setBlock(currentBlock);
    } else if (type == 'L') {
    	cellsForBlock.push_back(board.at(0).at(0));
        cellsForBlock.push_back(board.at(1).at(0));
        cellsForBlock.push_back(board.at(2).at(0));
        cellsForBlock.push_back(board.at(2).at(1));

    	currentBlock = make_shared<Block>(cellsForBlock, type, level->getLevel());

    	board.at(0).at(0)->setBlock(currentBlock);
    	board.at(1).at(0)->setBlock(currentBlock);
    	board.at(2).at(0)->setBlock(currentBlock);
    	board.at(2).at(1)->setBlock(currentBlock);
    } else if (type == 'O') {
    	cellsForBlock.push_back(board.at(1).at(0));
        cellsForBlock.push_back(board.at(1).at(1));
        cellsForBlock.push_back(board.at(2).at(0));
        cellsForBlock.push_back(board.at(2).at(1));

    	currentBlock = make_shared<Block>(cellsForBlock, type, level->getLevel());

    	board.at(1).at(0)->setBlock(currentBlock);
    	board.at(1).at(1)->setBlock(currentBlock);
    	board.at(2).at(0)->setBlock(currentBlock);
    	board.at(2).at(1)->setBlock(currentBlock);
    } else if (type == 'S') {
    	cellsForBlock.push_back(board.at(1).at(1));
        cellsForBlock.push_back(board.at(1).at(2));
        cellsForBlock.push_back(board.at(2).at(0));
        cellsForBlock.push_back(board.at(2).at(1));

    	currentBlock = make_shared<Block>(cellsForBlock, type, level->getLevel());

    	board.at(1).at(1)->setBlock(currentBlock);
    	board.at(1).at(2)->setBlock(currentBlock);
    	board.at(2).at(0)->setBlock(currentBlock);
    	board.at(2).at(1)->setBlock(currentBlock);
    } else if (type == 'T') {
    	cellsForBlock.push_back(board.at(1).at(0));
        cellsForBlock.push_back(board.at(1).at(1));
        cellsForBlock.push_back(board.at(1).at(2));
        cellsForBlock.push_back(board.at(2).at(1));

    	currentBlock = make_shared<Block>(cellsForBlock, type, level->getLevel());

    	board.at(1).at(0)->setBlock(currentBlock);
    	board.at(1).at(1)->setBlock(currentBlock);
    	board.at(1).at(2)->setBlock(currentBlock);
    	board.at(2).at(1)->setBlock(currentBlock);
    } else if (type == 'Z') {
    	cellsForBlock.push_back(board.at(1).at(0));
        cellsForBlock.push_back(board.at(1).at(1));
        cellsForBlock.push_back(board.at(2).at(1));
        cellsForBlock.push_back(board.at(2).at(2));

    	currentBlock = make_shared<Block>(cellsForBlock, type, level->getLevel());

    	board.at(1).at(1)->setBlock(currentBlock);
    	board.at(1).at(1)->setBlock(currentBlock);
    	board.at(2).at(1)->setBlock(currentBlock);
    	board.at(2).at(2)->setBlock(currentBlock);
    } else {
        cerr << "Block initialized with wrong type" << endl;
    }

	if(currentBlock == nullptr) getNextBlock();
    blocksOnBoard.push_back(currentBlock);

}

void QuadrisBoard::moveBlock(vector<pair<int,int>> coords) {
	//printCoords(coords);
	for(int i=currentBlock->getCells().size()-1; i>=0; i--) {
		currentBlock->getCells().at(i)->setBlock(nullptr);
		currentBlock->getCells().pop_back();
	}

	vector<shared_ptr<Cell>> newCells;

	for(int i=0; i<coords.size(); i++) {
		shared_ptr<Cell> theCell = board.at(coords.at(i).first).at(coords.at(i).second);
		theCell->setBlock(currentBlock);
		newCells.push_back(theCell);
	}
	currentBlock->setCells(newCells);

}

//Getters and Setters -------------------------------------------------------------

vector<vector<shared_ptr<Cell>>> QuadrisBoard::getBoard() { return board; }

void QuadrisBoard::setBoard(vector<vector<shared_ptr<Cell>>> newBoard) { board = newBoard; }

shared_ptr<Level> QuadrisBoard::getLevel() { return level; }

void QuadrisBoard::setLevels(shared_ptr<Level> newLevels) { level = newLevels; }

shared_ptr<Block> QuadrisBoard::getCurrentBlock() {
	return currentBlock;
}

void QuadrisBoard::setLevel(shared_ptr<Level> newLevel) {

	level = newLevel;

}
