#ifndef __RENDERABLE_H__
#define __RENDERABLE_H__

#include <string>

class Renderable {
public:
	virtual ~Renderable();
	virtual std::string render() = 0;
};

#endif
