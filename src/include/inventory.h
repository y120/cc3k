#ifndef __INVENTORY_H__
#define __INVENTORY_H__

#include <vector>

class AbstractItem;

class Inventory {
public:
	Inventory(int = 0);
	~Inventory();

	unsigned getSize() const;
	unsigned getCapacity() const;
	void setCapacity(int);
	void addCapacity(int);

	bool addItem(AbstractItem*);
	AbstractItem* getItem(unsigned) const;
	void removeItem(unsigned);

	std::vector<AbstractItem*>& getRaw();

private:
	int capacity;
	std::vector<AbstractItem*> contents;
};

#endif
