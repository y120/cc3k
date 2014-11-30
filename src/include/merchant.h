#ifndef __MERCHANT_H__
#define __MERCHANT_H__

#include "abstractEnemy.h"

class Merchant : public AbstractEnemy {
public:
	Merchant();

	void getHitBy(Player*);
	void strike(Player*);

	// Merchants are neutral by default, and need to be reset to neutral each
	// time we change floors.
	static void setHostile(bool);
	static bool isHostile();

	void doTurn();

private:
	static bool hostile;
};

#endif
