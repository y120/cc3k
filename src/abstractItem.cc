#include "abstractItem.h"

/**
 *	Constructor. Set the value and set the destroy flag to false.
 */
AbstractItem::AbstractItem(int value) : value(value) {}

// Destructor does nothing by default; it's here because it's virtual.
AbstractItem::~AbstractItem() {}

int AbstractItem::getValue() const {
	return this->value;
}
