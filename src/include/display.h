#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <iostream>
#include <vector>
#include "point.h"

class Renderable;

class Display {
	// Not implemented as part of singleton pattern
	Display();
	Display(const Display&);
	Display &operator=(const Display&);
	
	std::ostream* out;
	std::vector<std::string> screenBuffer;
	Point size;
public:
	static Display *getInstance();
	void setSource(std::ostream *);
	void resize(int row, int col);
	void draw(const Renderable *);
	void draw(const std::string &, int row = 0, int col = 0);
	void render() const;
};

#endif