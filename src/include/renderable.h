#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <string>

enum class ColourType {
	BLACK = 30,
	DRED,
	DGREEN,
	DYELLOW,
	DBLUE,
	DMAGENTA,
	DCYAN,
	GREY,
	DGREY = 90,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
};

class Renderable {
	std::string name;
	std::string sprite;
	ColourType colour;
protected:
	int r, c;
public:
	Renderable();
	Renderable(int, int);
	Renderable(std::string, int, int);
	virtual ~Renderable();
	virtual std::string getName() const;
	std::string getSprite() const;
	std::string getColour() const;
	int getR() const;
	int getC() const;
	void setName(const std::string &);
	void setSprite(const std::string &);
	void setColour(ColourType);
	void moveSprite(int row = 0, int col = 0);
	virtual void render();
};

#endif
