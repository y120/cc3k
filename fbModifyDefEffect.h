#ifndef __FB_MODIFY_DEF_EFFECT_H__
#define __FB_MODIFY_DEF_EFFECT_H__

#include "floorBoundEffect.h"

class FBModifyDefEffect : public FloorBoundEffect {
public:
	FBModifyDefEffect(Player *base, int floor, int modifier);

	// override the base getDef() function.
	int getDef() const;

	FBModifyDefEffect* clone();
private:
	int modifier;
};

#endif
