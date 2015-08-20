#ifndef JL_BASEBFSALGORITHM_H
#define JL_BASEBFSALGORITHM_H

#include "BfsInterface.h"

namespace joblevel
{

class BaseBfsHandler;
class BaseGameHandler;
/*!
	@brief	Base BFS algorithm implement BFS interface to maintain the whole
			JL-BFS algorithm, especially for tree traversal. Delegate BFS 
			handler and game handler to handle data of nodes.
	@author	chaochin
	@date	2015/7/18
 */
class BaseBfsAlgorithm : public BfsInterface
{
public:
	BaseBfsAlgorithm();
	virtual ~BaseBfsAlgorithm() {};
	BaseBfsHandler* getBfsHandler() const;
	void setBfsHandler(BaseBfsHandler* pBfsHandler);
	BaseGameHandler* getGameHandler() const;
	void setGameHandler(BaseGameHandler* pGameHandler);
	////////////////////////////////////
	// implementation of BfsInterface //
	////////////////////////////////////
	virtual bool initialize(NodePtr pNode);
	virtual NodePtr select();
	virtual void preUpdate(NodePtr pNode);
	virtual bool dispatch(NodePtr pNode);
	virtual NodePtr handleJobResult(int iJId, NodePtr pNode, const std::string& sResult);
	virtual void update(NodePtr pNode);
	virtual bool isCompleted();
	virtual void finalize();
	
	bool delayedExpand(NodePtr pNode);

private:
	bool shouldSelect();
	void update(NodePtr pLeaf, bool isPreUpdate);
	void generatePostponedSibling(NodePtr pNode);
	void restorePreUpdate(NodePtr pLeaf);

private:
	BaseBfsHandler* m_pBfsHandler;
	BaseGameHandler* m_pGameHandler;
	int m_nDoingJobs;
	int m_nTotalJobs;
};

}

#endif
