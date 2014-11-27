#ifndef __BA_POTION_H__
#define __BA_POTION_H__

#include "abstractPotion.h"

class AbstractEffect;

class BAPotion : public AbstractPotion {
public:
	BAPotion();
protected:
	std::string getNameInternal() const;
};

#endif
