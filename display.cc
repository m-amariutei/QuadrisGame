#include "display.h"

Display::Display(bool newGraphics, shared_ptr<QuadrisBoard> newBoard) {
	graphics = newGraphics;
	quadrisboard = newBoard;
}

bool Display::getGraphics() {
	return graphics;
}

void Display::setGraphics(bool newGraphics) {
	newGraphics = graphics;
}

void Display::print(bool showHidden, char empty) {
	if(graphics) {
		quadrisboard->print(showHidden, empty);
		//TODO: graphics

	} else {
		quadrisboard->print(showHidden, empty);
	}
}
