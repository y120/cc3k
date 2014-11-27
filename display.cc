#ifndef __DISPLAY_H__
#define __DISPLAY_H__

class Display {
public:
	static Display *getInstance();

private:
	Display();

	// Not implemented as part of singleton pattern
	Display(const Display&);
	Display &operator=(const Display&);
};

#endif