
#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <memory>
#include "window.h"
#include "quadrisboard.h"

using namespace std;

class QuadrisBoard;

class DisplayType {
	bool graphics;
	shared_ptr<QuadrisBoard> quadrisboard;

public:
    DisplayType(bool newGraphics, shared_ptr<QuadrisBoard> newBoard);
    //~Display();

    bool getGraphics();
    void setGraphics(bool newGraphics);

    void print(bool showHidden = true, char empty = ' ');
};

#endif
