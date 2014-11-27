#ifndef __PH_POTION_H__
#define __PH_POTION_H__

#include "abstractPotion.h"

class PHPotion : public AbstractPotion {
public:
	void apply();

protected:
	std::string getNameInternal() const;
};

#endif
