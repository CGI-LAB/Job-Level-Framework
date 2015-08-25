#ifndef JL_BFSRETRIEVER_H
#define JL_BFSRETRIEVER_H

#include "BfsData.h"

namespace joblevel
{

class BfsRetriever
{
public:
	virtual ~BfsRetriever() {}
	virtual BfsData::WinningStatus getWinningStatus() const = 0;
	virtual bool getStopExpanding() const = 0;
};

}

#endif // JL_BFSRETRIEVER_H
