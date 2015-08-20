#ifndef JL_BFSINTERFACE_H
#define JL_BFSINTERFACE_H

#include "AlgorithmInterface.h"

namespace joblevel
{

class BfsInterface : public AlgorithmInterface
{
public:
	BfsInterface() {}
	virtual ~BfsInterface() {}

	virtual bool requestJobs()
	{
		NodePtr pSelectedNode = select();
		if (pSelectedNode == nullptr)
			return false;
		bool bDispatched = dispatch(pSelectedNode);
		if (bDispatched == false)
			return false;
		preUpdate(pSelectedNode);
		return true;
	}

	virtual void receiveJobMessage(int iJId, NodePtr pNode, const std::string& sMessage)
	{
		NodePtr pNewNode = handleJobResult(iJId, pNode, sMessage);
		if (pNewNode == nullptr)
			return;

		update(pNewNode);
	}

	virtual bool initialize(NodePtr pNode) = 0;
	virtual NodePtr select() = 0;
	virtual void preUpdate(NodePtr pNode) = 0;
	virtual bool dispatch(NodePtr pNode) = 0;
	virtual NodePtr handleJobResult(int iJId, NodePtr pNode, const std::string& sMessage) = 0;
	virtual void update(NodePtr pNode) = 0;
	virtual bool isCompleted() = 0;
	virtual void finalize() = 0;

protected:
	NodePtr getJobLevelRoot() const
	{
		return m_pJobLevelRoot;
	}

	void setJobLevelRoot(NodePtr pNode)
	{
		m_pJobLevelRoot = pNode;
	}

private:
	NodePtr m_pJobLevelRoot;
};

}

#endif
