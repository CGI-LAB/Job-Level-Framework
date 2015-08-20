#ifndef JL_MINIMAXHANDLER_H
#define JL_MINIMAXHANDLER_H

#include "UctHandler.h"

namespace joblevel 
{

class MiniMaxHandler : public UctHandler
{
public:
	MiniMaxHandler();
	virtual ~MiniMaxHandler() {}
	virtual void updateSpecificData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate);
};

} // joblevel

#endif // JL_MINIMAXHANDLER_H
