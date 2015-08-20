#ifndef JL_UCTPARSERINTERFACE_H
#define JL_UCTPARSERINTERFACE_H

#include <string>

namespace joblevel
{

class UctParserInterface
{
public:
	virtual double getWinRate(const std::string& sResult) const = 0;
};

}

#endif
