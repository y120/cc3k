#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <string>

class Renderable {
	std::string name;
	std::string sprite;
protected:
	int r, c;
public:
	Renderable();
	Renderable(int, int);
	Renderable(std::string, int, int);
	virtual ~Renderable();
	std::string getName() const;
	std::string getSprite() const;
	int getR() const;
	int getC() const;
	void setName(const std::string &);
	void setSprite(const std::string &);
	void move(int row = 0, int col = 0);
	virtual void render();
};

#endif
