
#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <memory>
#include "quadrisboard.h"

using namespace std;

class QuadrisBoard;

class Display {
	bool graphics;
	shared_ptr<QuadrisBoard> quadrisboard;

public:
    Display(bool newGraphics, shared_ptr<QuadrisBoard> newBoard);
    //~Display();

    bool getGraphics();
    void setGraphics(bool newGraphics);

    void print(bool showHidden = true, char empty = ' ');
};

#endif
