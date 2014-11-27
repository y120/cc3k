#ifndef __CHARACTER_IMPL_H__
#define __CHARACTER_IMPL_H__

struct CharacterImpl {
	struct CharacterStats {
		int hp, maxhp, atk, def, dodge;
	} stats;

	struct CharacterPosition {
		// position on floor -- x[0, 80) y[0, 30]
		int r, c;
	} pos;
};

#endif
