#ifndef JL_UCTRETRIEVER_H
#define JL_UCTRETRIEVER_H

#include "BfsRetriever.h"

namespace joblevel
{

class UctRetriever
	: public BfsRetriever
{
public:
	virtual ~UctRetriever() {}
	virtual double getWinRate() const = 0;
};

}

#endif
