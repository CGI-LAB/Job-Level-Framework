#include "BaseBfsAlgorithm.h"
#include <vector>
#include <sstream>
#include <cassert>
#include <fstream>
#include "JobLevelConfigure.h"
#include "BaseBfsHandler.h"
#include "BaseGameHandler.h"

namespace joblevel
{

BaseBfsAlgorithm::BaseBfsAlgorithm()
	: BfsInterface(),
	  m_pBfsHandler(NULL),
	  m_pGameHandler(NULL),
	  m_nDoingJobs(0),
	  m_nTotalJobs(0)
{
	if (JobLevelConfigure::g_configure.bUseJobLog) {
		std::ofstream fout(JobLevelConfigure::g_configure.sJobLogFile.c_str());
		fout << "Start: " << std::endl;
		fout.close();
	}
}

BaseBfsHandler* BaseBfsAlgorithm::getBfsHandler() const
{
	assert(m_pBfsHandler != NULL);
	return m_pBfsHandler;
}

void BaseBfsAlgorithm::setBfsHandler(BaseBfsHandler* pBfsHandler)
{
	m_pBfsHandler = pBfsHandler;
}

BaseGameHandler* BaseBfsAlgorithm::getGameHandler() const
{
	return m_pGameHandler;
}

void BaseBfsAlgorithm::setGameHandler(BaseGameHandler* pGameHandler)
{
	m_pGameHandler = pGameHandler;
}

bool BaseBfsAlgorithm::initialize(NodePtr pNode)
{
	assert(m_pBfsHandler != NULL);
	assert(m_pGameHandler != NULL);
	m_nTotalJobs = 0;
	setJobLevelRoot(pNode);
	std::vector<NodePtr> vNodes;
	NodePtr pTraversedNode = pNode;
	while (pTraversedNode != nullptr) {
		vNodes.push_back(pTraversedNode);
		pTraversedNode = pTraversedNode->getParent();
	}
	for (std::vector<NodePtr>::reverse_iterator rit = vNodes.rbegin(); rit != vNodes.rend(); ++rit) {
		m_pBfsHandler->initializeNode(*rit);
		m_pGameHandler->initializeNode(*rit);
	}
	return true;
}

NodePtr BaseBfsAlgorithm::select()
{
	if (shouldSelect() == false)
		return nullptr;

	NodePtr pSelectedNode = getJobLevelRoot();
	assert(m_pBfsHandler != NULL);
	if (m_pBfsHandler->isProvenNode(pSelectedNode))
		return nullptr;

	NodePtr pBestChildNode = m_pBfsHandler->selectBestChild(pSelectedNode);
	while (pBestChildNode != nullptr) {
		pSelectedNode = pBestChildNode;
		if (m_pBfsHandler->isLastestGenerated(pSelectedNode))
			generatePostponedSibling(pSelectedNode);
		pBestChildNode = m_pBfsHandler->selectBestChild(pSelectedNode);
	}

	if (pSelectedNode == getJobLevelRoot() && 
		(m_pBfsHandler->isRunningJob(pSelectedNode) || m_pBfsHandler->isFlagged(pSelectedNode)))
		return nullptr;

	return pSelectedNode;
}

void BaseBfsAlgorithm::preUpdate(NodePtr pNode)
{
	update(pNode, true);
}

bool BaseBfsAlgorithm::dispatch(NodePtr pNode)
{
	assert(m_pBfsHandler != NULL);
	assert(m_pGameHandler != NULL);
	std::ostringstream oss;
	if (m_pBfsHandler->isRunningJob(pNode)) {
		oss << "Error : the node to dispathch is running job" << std::endl;
		std::cerr << oss.str() << "> " << std::flush;
		pNode->appendComment(oss.str());
		return false;
	} else if (m_pBfsHandler->isFlagged(pNode)) {
		oss << "Error : the node to dispatch is flagged" << std::endl;
		std::cerr << oss.str() << "> " << std::flush;
		pNode->appendComment(oss.str());
		return false;
	}

	std::string sAppName = m_pGameHandler->getAppName();
	std::string sAppVersion = m_pGameHandler->getAppVersion();
	std::string sArgument = m_pGameHandler->getArgument(pNode);

	int iJId = submitJob(pNode, sAppName, sAppVersion, sArgument);

	oss.str("");
	oss << "Submit job ID " << iJId << ": " << sArgument << std::endl;
	pNode->appendComment(oss.str());

	if (JobLevelConfigure::g_configure.bUseJobLog) {
		std::ofstream fout(JobLevelConfigure::g_configure.sJobLogFile.c_str(), std::ios::app);
		fout << oss.str();
		fout.close();
	}

	m_nDoingJobs++;
	m_nTotalJobs++;
	return true;
}

NodePtr BaseBfsAlgorithm::handleJobResult(int iJId, NodePtr pNode, const std::string& sResult)
{
	m_nDoingJobs--;
	assert(m_pBfsHandler != NULL);
	assert(m_pGameHandler != NULL);
	std::ostringstream oss;
	if (m_pGameHandler->isNodeAlreadyExist(pNode, sResult)) {
		if (m_pGameHandler->handleDuplicateNode(pNode)) {
			oss << std::endl << "Handle duplicate node: Set StopExpanding true" << std::endl << "Receive job ID " << iJId 
				<< ": " << sResult << std::endl;
			pNode->appendComment(oss.str());
		} else {
			oss << "Error: New node already exist, JID: " << iJId
					  << ", Result: " << sResult << std::endl;
			std::cerr << oss.str() << "> " << std::flush;
			pNode->appendComment(oss.str());
		}
		restorePreUpdate(pNode);
		return nullptr;
	}
	NodePtr pNewNode = m_pGameHandler->generateNode(pNode, sResult);

	oss.str("");
	oss << "Receive job ID " << iJId << ": " << sResult << std::endl;
	pNewNode->appendComment(oss.str());

	if (JobLevelConfigure::g_configure.bUseJobLog) {
		std::ofstream fout(JobLevelConfigure::g_configure.sJobLogFile.c_str(), std::ios::app);
		fout << oss.str();
		fout.close();
	}

	m_pBfsHandler->setupBfsData(pNewNode, sResult);
	m_pGameHandler->setupGameData(pNewNode, sResult);

	return pNewNode;
}

void BaseBfsAlgorithm::update(NodePtr pNode)
{
	update(pNode, false);
}

bool BaseBfsAlgorithm::isCompleted()
{
	// If root is proved or total jobs hit node limit, algorithm is completed.
	assert(m_pBfsHandler != NULL);
	if (m_pBfsHandler->isProvenNode(getJobLevelRoot()) ||
		m_nTotalJobs >= JobLevelConfigure::g_configure.iJobLimit)
		return true;
	return false;
}

void BaseBfsAlgorithm::finalize()
{
	std::cout << "Job level Finished" << std::endl << "> " << std::flush;
}

bool BaseBfsAlgorithm::shouldSelect()
{
	int nMaxRunningJobs = JobLevelConfigure::g_configure.nMaxRunningJobs;
	return hasWaitingJob() == false && 
		(m_nDoingJobs < nMaxRunningJobs || nMaxRunningJobs == 0);
}

void BaseBfsAlgorithm::update(NodePtr pLeaf, bool isPreUpdate)
{
	assert(m_pBfsHandler != NULL);
	NodePtr pTraversedChild = pLeaf;
	while (pTraversedChild != nullptr) {
		m_pBfsHandler->updateBfsData(pTraversedChild, pLeaf, isPreUpdate);
		pTraversedChild = pTraversedChild->getParent();
	}
	NodePtr pUpdateNode = isPreUpdate?pLeaf:pLeaf->getParent();
	m_pBfsHandler->updateRunningJobFlag(pUpdateNode, isPreUpdate);
	m_pBfsHandler->updateWithFlagPolicy(pUpdateNode, isPreUpdate);
	if (isPreUpdate == false)
		m_pBfsHandler->proveNodesRetrograde(pLeaf, *this);
}

void BaseBfsAlgorithm::generatePostponedSibling(NodePtr pNode)
{
	delayedExpand(pNode);
}

bool BaseBfsAlgorithm::delayedExpand(NodePtr pNode)
{
	assert(m_pBfsHandler != NULL);
	if (pNode->isRoot())
		return false;
	NodePtr pParent = pNode->getParent();
	if (pParent->getSequence() < getJobLevelRoot()->getSequence() ||
		m_pBfsHandler->shouldDelayedExpand(pNode) == false)
		return false;
	if (dispatch(pParent)) {
		preUpdate(pParent);
		return true;
	}
	return false;
}

void BaseBfsAlgorithm::restorePreUpdate(NodePtr pLeaf)
{
	assert(m_pBfsHandler != NULL);
	NodePtr pTraversedChild = pLeaf;
	while (pTraversedChild != nullptr) {
		m_pBfsHandler->restoreUpdateBfsData(pTraversedChild, pLeaf);
		pTraversedChild = pTraversedChild->getParent();
	}
	m_pBfsHandler->updateRunningJobFlag(pLeaf, false);
	m_pBfsHandler->updateWithFlagPolicy(pLeaf, false);
}

}
