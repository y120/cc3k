#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <iostream>
#include <vector>

class Renderable;

class Display {
	// Not implemented as part of singleton pattern
	Display();
	Display(const Display&);
	Display &operator=(const Display&);
	
	std::ostream* out;
	std::vector<std::string> screenBuffer;
	int rSize, cSize;

	// message containers
	std::vector<std::string> messageHistory;
public:
	static Display *getInstance();
	void setOutput(std::ostream *);
	void resize(int row, int col);
	void addMessage(const std::string &);
	void drawMessage();
	void draw(const Renderable *);
	void draw(const std::string &, int row = 0, int col = 0);
	void render();
};

#endif