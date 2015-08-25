#ifndef JL_COMMONBFJLMODULES_H
#define JL_COMMONBFJLMODULES_H

#include "BfsInterface.h"

namespace joblevel
{

class BfsHandler;
class GameHandler;
class Integrator;
/*!
	@brief	Base BFS algorithm implement BFS interface to maintain the whole
			JL-BFS algorithm, especially for tree traversal. Delegate BFS 
			handler and game handler to handle data of nodes.
	@author	chaochin
	@date	2015/7/18
 */
class CommonBfJlModules : public BfsInterface
{
public:
	CommonBfJlModules();
	virtual ~CommonBfJlModules() {};
	BfsHandler* getBfsHandler() const;
	void setBfsHandler(BfsHandler* pBfsHandler);
	GameHandler* getGameHandler() const;
	void setGameHandler(GameHandler* pGameHandler);
	Integrator* getIntegrator() const;
	void setIntegrator(Integrator* pIntegrator);
	////////////////////////////////////
	// implementation of BfsInterface //
	////////////////////////////////////
	virtual bool initialize(NodePtr pNode);
	virtual NodePtr select();
	virtual void preUpdate(NodePtr pNode);
	virtual bool dispatch(NodePtr pNode);
	virtual NodePtr handleResult(int iJId, NodePtr pNode, const std::string& sResult);
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
	BfsHandler* m_pBfsHandler;
	GameHandler* m_pGameHandler;
	Integrator* m_pIntegrator;
	int m_nDoingJobs;
	int m_nTotalJobs;
};

}

#endif
