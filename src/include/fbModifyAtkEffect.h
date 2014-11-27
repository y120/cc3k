#ifndef __FB_MODIFY_ATK_EFFECT_H__
#define __FB_MODIFY_ATK_EFFECT_H__

#include "floorBoundEffect.h"

class FBModifyAtkEffect : public FloorBoundEffect {
public:
	FBModifyAtkEffect(Player *base, int floor, int modifier);

	// override the base getAtk() function.
	int getAtk() const;

	FBModifyAtkEffect* clone();
private:
	int modifier;
};

#endif
