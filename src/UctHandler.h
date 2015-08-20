#ifndef JL_UCTHANDLER_H
#define JL_UCTHANDLER_H

#include "BaseBfsHandler.h"

namespace joblevel
{

class UctParserInterface;

class UctHandler : public BaseBfsHandler
{
public:
	UctHandler();
	virtual ~UctHandler() {}
	NodePtr selectBestChild(NodePtr pParent);
	bool setBaseJMsgParser(BaseJMsgParser* pBaseJMsgParser);

protected:
	void initializeSpecificData(NodePtr pNode);
	void setupSpecificData(NodePtr pNode, const std::string& sResult);
	virtual void updateSpecificData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate);
	void restoreUpdateSpecificData(NodePtr pChild, NodePtr pLeaf);
	void updateUcbScore(NodePtr pParent);

private:
	UctParserInterface* m_pUctParserInterface;
};

}

#endif
