#ifndef __DLC_H__
#define __DLC_H__

enum class DLC {
	/*
	 *	Generated DLC
	 *	=============
	 *	When active, randomly generates a dungeon rather than using the default.
	 */
	Generated,
	/*
	 *	Inventory DLC
	 *	=============
	 *	Enables the pickup of potions, weapons, armours, etc. When active, gold
	 *	piles must be picked up explicitly; they are not automatically added to
	 *	the player's total.
	 */
	Inventory,
	/*
	 *	WASD DLC
	 *	========
	 *	Enables WASD movement.
	 */
	//WASD,
	/*
	 *	Fog of War DLC
	 *	==============
	 *	You don't get perfect knowledge anymore!
	 */
	FogOfWar,
	/*
	 *	Colour DLC
	 *	==========
	 *	Finally, you can see your ASCII player, tile and enemy sprites
	 *	in glorious 4-bit colour!
	 */
	Colour,
	LAST
};

#endif
