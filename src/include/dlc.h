#ifndef __DLC_H__
#define __DLC_H__

enum class DLC {
	/*
	 *	Inventory DLC
	 *	=============
	 *	Enables the pickup of potions, weapons, armours, etc. When active, gold
	 *	piles must be picked up explicitly; they are not automatically added to
	 *	the player's total.
	 */
	Inventory,
	/*
	 *	Alchemistry DLC
	 *	===============
	 *	Provides additional potions, some with temporary (not floor-bound)
	 *	effects. Also increases the potion spawn limit to 30. List of potions
	 *	added:
	 *	(May be sold by Merchants)
	 *	- Potion of Candlesticks: +25% dodge / 10 turns
	 *	- Potion of Fleeting Strength: +5 Atk / 5 turns
	 *	- Potion of Fleeting Tenacity: +5 Def / 5 turns
	 *	- Potion of Berserking Rage: +10 Atk, -5 Def / 10 turns
	 *	- Greater Potion of Berserking Rage: +40 Atk, -10 Def, -50% dodge / 10 turns
	 *	- Potion of Recklessness: +15 Atk, -25% dodge / 10 turns
	 *	- Lesser Potion of Demonic Strength: +10 Atk, -50% MaxHP / 5 turns
	 *	- Potion of Demonic Strength: +15 Atk, -50% MaxHP / 10 turns
	 *	- Lesser Potion of the Tortoise: +10 MaxHP / 10 turns
	 *	- Potion of the Tortoise: +20 MaxHP, +10 Def / 10 turns
	 *	- Lesser Potion of Regeneration: +2 HP per turn / 4 turns
	 *	- Potion of Regeneration: +3 HP per turn / 5 turns
	 *	- Lesser Scroll of Shadow Clones: +5 Atk, -50% MaxHP, +25% dodge / 5 turns
	 *	- Scroll of Shadow Clones: +8 Atk, -80% MaxHP, +40% dodge / 5 turns
	 *	- Greater Scroll of Shadow Cones: +10 Atk, -99% MaxHP, +49% dodge / 5 turns
	 *	- Potion of Near-Invincibility: +100 Def / 2 turns
	 *
	 *	(Only purchaseable from Merchant)
	 *	- Scroll of Evil: +25 Atk, -50% MaxHP / indefinite
	 *	- Scroll of Self-Defense: -10 Atk, +20 Def / indefinite
	 *	- Scroll of the Wallflower: -15 Atk, +30% Dodge / indefinite
	 *	- Scroll of the Ninja: +10 Atk, +30% Dodge, -80% MaxHP, -10 Def / indefinite
	 *	- All-or-Nothing Scroll: -90% MaxHP, +40% Dodge / indefinite
	 *
	 *	(Appears as a potion. Cannot be sold by Merchants)
	 *	- Poison of Clumsiness: -25% dodge / 10 turns
	 *	- Lesser Poison of Weakness: -5 Atk / 10 turns
	 *	- Lesser Poison of Fragility: -5 Def / 10 turns
	 *	- Lesser Poison of Frailty: -20 MaxHP / 10 turns
	 *	- Poison of Poison: -5 HP per turn / 5 turns
	 *	- Greater Poison of Poison: -15 HP per turn / 3 turns
	 */
	Alchemistry,
	/*
	 *	Equipment DLC
	 *	=============
	 *	Permits the wearing of Weapons and Armour. Weapons provide an attack
	 *	modifier, while Armours provide a defense modifier. Only one of each may
	 *	be worn at a time.
	 */
	Equipment,
	/*
	 *	Survival DLC
	 *	============
	 *	No win condition. Enemies gain +5 Atk / +5 Def / +10 MaxHP per 5 floors.
	 *	The Player gains +10 MaxHP / +10 Gold per 5 floors.
	 */
	Survival,
	/*
	 *	Merchant DLC
	 *	============
	 *	Merchants no longer wander, unless unfriendly. Merchants will be able to
	 *	trade items with the Player. Merchants now come in four states, in order
	 *	of priority:
	 *
	 *	- Neutral (default):
	 *			Player may purchase or sell items.
	 *	- Friendly:
	 *			After 5 completed trades, Merchants give a 10% discount when
	 *			purchasing items. Sell value is not affected.
	 *	- Unfriendly:
	 *			If a Player has ever attacked a Merchant, all Merchants will be
	 *			unfriendly. Prices will be marked up by 20% and sell value is
	 *			reduced by 10%. Some Merchants may choose not to trade with the
	 *			Player at all.
	 *	- Hostile: 
	 *			If a Player has attacked a Merchant on this floor, all Merchants
	 *			on this floor will become hostile and actively pursue the Player.
	 */
	Merchant,
	/*
	 *	WASD DLC
	 *	========
	 *	Enables WASD movement.
	 */
	WASD,
	/*
	 *	Fog of War DLC
	 *	==============
	 *	You don't get perfect knowledge anymore!
	 */
	FogOfWar
};

#endif
