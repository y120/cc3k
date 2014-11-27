#ifndef __FLOOR_BOUND_EFFECT_H__
#define __FLOOR_BOUND_EFFECT_H__

#include "abstractPlayerEffect.h"

class FloorBoundEffect : public AbstractPlayerEffect {
public:
	// A FloorBoundEffect expires when the floor is no longer the current floor.
	// Since AbstractEffect decorates a Character, we can just check that the
	// floors match.
	bool isExpired() const;

protected:
	FloorBoundEffect(Player *base, int floor);

	int floor;
};

#endif
