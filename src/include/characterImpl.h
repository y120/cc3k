#ifndef __CHARACTER_IMPL_H__
#define __CHARACTER_IMPL_H__

struct CharacterImpl {
	struct CharacterStats {
		int hp, maxhp, atk, def, dodge;
	} stats;

	int floor;
};

#endif
