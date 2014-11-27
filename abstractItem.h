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

	// After being picked up, the destroy flag is set. If the shouldDestroy flag
	// is set then we delete; otherwise we just set to NULL (it'll have been
	// added to the Inventory).
	bool shouldDestroy() const;

	// do not implement render()!

protected:
	int value;
	bool destroy;
};

#endif
