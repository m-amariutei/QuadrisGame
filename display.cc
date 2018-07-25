#include "display.h"

DisplayType::DisplayType(bool newGraphics, shared_ptr<QuadrisBoard> newBoard) {
	graphics = newGraphics;
	quadrisboard = newBoard;
}

bool DisplayType::getGraphics() {
	return graphics;
}

void DisplayType::setGraphics(bool newGraphics) {
	newGraphics = graphics;
}

void DisplayType::printT(bool showHidden, char empty) {
	if(graphics) {

		quadrisboard->printText(showHidden, empty);

	} else {

		quadrisboard->printGraphic(showHidden);
	}
}
