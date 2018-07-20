#include "quadrisboard.h"

QuadrisBoard::QuadrisBoard() {
	for(int i=0; i<HEIGHT; i++) {
		vector<Cell*> row;
		board.push_back(row);
		for(int j=0; j<WIDTH; j++) {
			Cell* cell = new Cell;	//need manual destroy
			board.at(i).push_back(cell);
		}
	}

	currentBlockIndex = -1;	//no blocks
	//levels 
	//display
}

QuadrisBoard::~QuadrisBoard() {
	for(int i=0; i<HEIGHT; i++) {
		for(int j=0; j<WIDTH; j++) {
			delete board.at(i).at(j);	//deleting cells
		}
	}
}

//Getters and Setters -------------------------------------------------------------

vector<vector<Cell *>> QuadrisBoard::getBoard() {
	return board;
}

void QuadrisBoard::setBoard(vector<vector<Cell *>> newBoard) {
	board = newBoard;
}

vector<Block *> QuadrisBoard::getBlocksOnBoard() {
	return blocksOnBoard();
}

void QuadrisBoard::setBlocksOnBoard(vector<Block *> newBlocksOnBoard) {
	blocksOnBoard = newBlocksOnBoard;
}

int QuadrisBoard::getCurrentBlockIndex() {
	return currentBlockIndex;
}

void QuadrisBoard::setCurrentBlockIndex(int newCurrentBlockIndex) {
	currentBlockIndex = newCurrentBlockIndex;
}

vector<Level> QuadrisBoard::getLevels() {
	return levels;
}

void QuadrisBoard::setLevels(vector<Level> newLevels) {
	levels = newLevels;
}

int QuadrisBoard::getCurrentLevel() {
	return currentLevel;
}

void QuadrisBoard::setCurrentLevel(int newCurrentLevel) {
	currentLevel = newCurrentLevel;
}

//--------------------------------------------------------------------------------

bool QuadrisBoard::isLost() {
	for(int i=0; i<WIDTH; i++) {
		if(board.at(LOST_ROW).at(i)->getBlock() != NULL) return true;
	}
	return false;
}

void QuadrisBoard::print(bool seeInvisible) {
	int begRow = 0;
	if(seeInvisible) begRow = NUM_ROWS_INVISIBLE;

	for(int i=begRow; i<HEIGHT; i++) {
		for(int j=0; j<WIDTH; j++) {
			Block* block = cout<<board.at(i).at(j)->getBlock();
			if(block != NULL) {
				cout<<block->getName();
			} else {
				cout<<' ';
			}
			
		}
		cout<<endl;
	}
}

void QuadrisBoard::executeCommand(string name) {
	//TODO
}

bool QuadrisBoard::isFullRow(int rowIndex) {
	if(rowIndex >= HEIGHT) cerr << "QuadrisBoard::isFullRow: rowIndex >= HEIGHT" <<endl;
	for(int i=0; i<WIDTH; i++) {
		if(board.at(rowIndex).at(i)->getBlock() == NULL) return false;
	}
	return true;
}

bool QuadrisBoard::deleteCellFromBlock(Block* block, int x, int y) {
	for(int j=0; j<block->getCells().length(); j++) {
		if(block->getCells().at(j)->xValue == x &&
			block->getCells().at(j)->yValue == y) {
			vector<Cell*>::iterator itt = block->getCells().begin() + j;
			block->getCells().erase(itt);
			return true;
		}
	}
	return false;
}

void QuadrisBoard::clearRow(int rowIndex) {
	if(rowIndex >= HEIGHT) cerr << "QuadrisBoard::clearRow: rowIndex >= HEIGHT" <<endl;
	if(!isFullRow(rowIndex)) cerr << "uadrisboard.cc/clearRow: called on non-full row" <<endl;
	for(int i=0; i<WIDTH; i++) {
		//let both cell and block know about this
		Cell* cell = board.at(rowIndex).at(i);
		Block* block = cell->getBlock();
		if(block == NULL) cerr << "quadrisboard.cc/clearRow: block should not be NULL here" <<endl;

		cell->setBlock(NULL);
		bool wasDeletedSuccessfully = false;
		wasDeletedSuccessfully = deleteCellFromBlock(block, cell->getXValue(), cell->getYValue());
		if(!wasDeletedSuccessfully) cerr << "quadrisboard.cc/clearRow: we deleted row " << rowIndex << "but failed to clear block->cells.at(" << i << ")" <<endl;
	}

	dropRowsAbove(rowIndex);
}

void QuadrisBoard::dropRowsAbove(int rowIndex) {
	if(rowIndex >= HEIGHT) cerr << "QuadrisBoard::dropRowsAbove: rowIndex >= HEIGHT" <<endl;
	for(int i = rowIndex; i<LOST_ROW; i--) {
		for(int j=0; j<WIDTH; j++) {
			dropTop(rowIndex, j);
		}
	}
}

void QuadrisBoard::dropTop(int rowIndex, int colIndex) {
	if(rowIndex >= HEIGHT || rowIndex < LOST_ROW) cerr << "QuadrisBoard::dropTop: rowIndex is wrong" <<endl;
	if(colIndex >= WIDTH || colIndex < 0) cerr << "QuadrisBoard::dropTop: colIndex is wrong" <<endl;

	//take care of both cell and block class
	Cell* cellDown = board.at(rowIndex).at(colIndex);
	//Block* blockDown = cell->block;
	Cell* cellTop = board.at(rowIndex - 1).at(colIndex);
	Block* blockTop = cellTop->getBlock();

	cellDown->setBlock(blockTop);
	cellTop->setBlock(NULL);
	//find Cell* in block that is above and replace it with a Cell* of the cell below
	bool wasDeletedSuccessfully = deleteCellFromBlock(blockTop, cellTop->getXValue(), cellDown->getYValue());
	if(!wasDeletedSuccessfully) cerr << "quadrisboard.cc/dropTop: deleteCellFromBlock failed" <<endl;
	blockTop->getCells()->push_back(cellDown);
}

bool QuadrisBoard::isBlockStuck(Block* block) {
	//return true iff below any cell occupied by this block, there is a cell occupied by another block or board ends
	for(int i=0; i<block->getCells().length(); i++) {
		if(cellBelowIsSticky(block, block->getCells.at(i).getXValue(), block->getCells.at(i).getYValue())) return true;
	}
	return false;
}

bool QuadrisBoard::cellBelowIsSticky(Block* block, int x, int y) {
	//Y is ROW and X is col
	if(y == HEIGHT - 1) return true;	//end of board reached
	else {
		Cell* cellBelow = board.at(y).at(x);
		if(cellBelow->getBlock() != block) return true;
		else return false;
	}
}

Interpreter * QuadrisBoard::patternMatchName(string name) {
	//TODO
	return NULL;
}
