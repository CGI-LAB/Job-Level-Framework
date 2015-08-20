#ifndef JL_BASECONFIGURE_H
#define JL_BASECONFIGURE_H

#include "ConfigureLoader.h"

namespace joblevel
{
/*!
	@brief	interface of Configure, used by Arguments
	@author	chaochin
	@date	2015/7/13
 */
class BaseConfigure
{
protected:
	BaseConfigure() {};
	BaseConfigure(const BaseConfigure&);
	BaseConfigure& operator=(const BaseConfigure&);

public:
	virtual void setConfigureOptions(ConfigureLoader& cl) = 0;
};

}

#endif
