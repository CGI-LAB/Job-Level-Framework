#ifndef JL_UCTHANDLER_H
#define JL_UCTHANDLER_H

#include "BfsHandler.h"

namespace joblevel
{

class UctRetriever;

class UctHandler : public BfsHandler
{
public:
	UctHandler();
	virtual ~UctHandler() {}
	virtual NodePtr selectBestChild(NodePtr pParent);

protected:
	virtual void initializeSpecificData(NodePtr pNode);
	virtual void setupSpecificData(NodePtr pNode, BfsRetriever* pBfsRetriever);
	virtual void updateSpecificData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate);
	virtual void restoreUpdateSpecificData(NodePtr pChild, NodePtr pLeaf);
	void updateUcbScore(NodePtr pParent);
};

}

#endif
