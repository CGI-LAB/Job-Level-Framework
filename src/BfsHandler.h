#ifndef JL_BFSHANDLER_H
#define JL_BFSHANDLER_H

#include "Node.h"
#include <string>

namespace joblevel
{

class CommonBfJlModules;
class GameParser;
/*!
	@brief	For handling BFS data, including update flag and prove positions.
			For different BFS algorithm (PNS, UCT, ...), inherit and implement
			the handler for their specific data.
	@author	chaochin
	@date	2015/7/23
 */
class BfsHandler
{
public:
	BfsHandler();
	virtual ~BfsHandler() {}
	void initializeNode(NodePtr pNode);
	bool isProvenNode(NodePtr pNode);
	bool isLastestGenerated(NodePtr pNode);
	bool isRunningJob(NodePtr pNode);
	bool isFlagged(NodePtr pNode);
	void setupBfsData(NodePtr pNode, const std::string& sResult);
	void updateBfsData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate);
	void restoreUpdateBfsData(NodePtr pChild, NodePtr pLeaf);
	void updateRunningJobFlag(NodePtr pNode, bool isRunningJob);
	void updateWithFlagPolicy(NodePtr pNode, bool isFlagged);
	void proveNodesRetrograde(NodePtr pNode, CommonBfJlModules& baseBfsAlgorithm);
	bool shouldDelayedExpand(NodePtr pNode);
	///////////////////////////////////////////////////
	// Need to implement in different BFS algorithms //
	///////////////////////////////////////////////////
	virtual NodePtr selectBestChild(NodePtr pParent) = 0;
	virtual bool setBaseJMsgParser(GameParser* pBaseJMsgParser) = 0;

protected:
	virtual void initializeSpecificData(NodePtr pNode) = 0;
	virtual void setupSpecificData(NodePtr pNode, const std::string& sResult) = 0;
	virtual void updateSpecificData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate) = 0;
	virtual void restoreUpdateSpecificData(NodePtr pChild, NodePtr pLeaf) = 0;

private:
	void updateFlaggedOn(NodePtr pNode);
	void updateFlaggedOff(NodePtr pNode);
};

}

#endif
