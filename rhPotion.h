#ifndef __RH_POTION_H__
#define __RH_POTION_H__

#include "abstractPotion.h"

class RHPotion : public AbstractPotion {
public:
	std::string getType() const;

	void apply();
protected:
	std::string getNameInternal() const;
};

#endif
