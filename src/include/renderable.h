#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <string>
#include "point.h"

class Renderable {
	std::string name;
	std::string sprite;
	Point pos;
public:
	Renderable();
	Renderable(std::string, int, int);
	virtual ~Renderable();
	std::string getName() const;
	std::string getSprite() const;
	Point getPosition() const;
	void setName(const std::string &);
	void setSprite(const std::string &);
	void move(const Point &);
	void move(int row = 0, int col = 0);
};

#endif
