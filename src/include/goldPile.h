#ifndef __GOLD_PILE_H__
#define __GOLD_PILE_H__

#include "abstractItem.h"

class GoldPile : public AbstractItem {
public:
	enum GoldPileSize {
		SmallPile     = 1,
		NormalPile    = 2,
		MerchantHoard = 4,
		DragonHoard   = 6
	};

	explicit GoldPile(GoldPileSize size);

	virtual bool canPickUp() const;
	void pickUp();
};

#endif
