#ifndef __ABSTRACT_ITEM_H__
#define __ABSTRACT_ITEM_H__

#include "renderable.h"

class AbstractItem : public Renderable {
public:
	explicit AbstractItem(int value);
	virtual ~AbstractItem();

	virtual bool canPickUp() const = 0;
	// Different items have different pick up behaviours!
	virtual void pickUp() = 0;

	int getValue() const;
	virtual std::string getName(bool) const;

	// do not implement render()!

protected:
	int value;
};

#endif
