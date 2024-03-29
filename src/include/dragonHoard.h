#ifndef __DRAGON_HOARD_H__
#define __DRAGON_HOARD_H__

#include "goldPile.h"

class Dragon;

class DragonHoard : public GoldPile {
public:
	DragonHoard();
	DragonHoard(Dragon*);

	void setDragon(Dragon*);

	bool canPickUp() const;
private:
	Dragon *dragon;
};

#endif
