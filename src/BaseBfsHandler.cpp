#include "BaseBfsHandler.h"
#include <cassert>
#include "BfsData.h"
#include "JobLevelConfigure.h"
#include "BaseBfsAlgorithm.h"

namespace joblevel
{

BaseBfsHandler::BaseBfsHandler()
{
}

void BaseBfsHandler::initializeNode(NodePtr pNode)
{
	BfsData::Accessor nodeData(pNode);
	initializeSpecificData(pNode);
}

bool BaseBfsHandler::isProvenNode(NodePtr pNode)
{
	BfsData::Accessor nodeData(pNode);
	return nodeData.getWinningStatus() != BfsData::UNKNOWN;
}

bool BaseBfsHandler::isLastestGenerated(NodePtr pNode)
{
	BfsData::Accessor nodeData(pNode);
	assert(pNode->hasParent());
	return nodeData.getSequenceOfGeneration() == pNode->getParent()->getChildrenSize();
}

bool BaseBfsHandler::isRunningJob(NodePtr pNode)
{
	BfsData::Accessor nodeData(pNode);
	return nodeData.isRunningJob();
}

bool BaseBfsHandler::isFlagged(NodePtr pNode)
{
	BfsData::Accessor nodeData(pNode);
	return nodeData.isFlagged();
}

void BaseBfsHandler::setupBfsData(NodePtr pNode, const std::string& sResult)
{
	BfsData::Accessor nodeData(pNode);
	assert(pNode->hasParent());
	nodeData.setSequenceOfGeneration(pNode->getParent()->getChildrenSize());
	setupSpecificData(pNode, sResult);
}

void BaseBfsHandler::updateBfsData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate)
{
	if (pChild->isRoot())
		return;
	BfsData::Accessor nodeData(pChild);
	BfsData::Accessor parentData(pChild->getParent());
	if (isPreUpdate) {
		if (pChild == pLeaf)
			nodeData.increaseUnderRunningJobs();
		parentData.increaseUnderRunningJobs();
	} else {
		parentData.decreaseUnderRunningJobs();
	}
	updateSpecificData(pChild, pLeaf, isPreUpdate);
}

void BaseBfsHandler::restoreUpdateBfsData(NodePtr pChild, NodePtr pLeaf)
{
	if (pChild->isRoot())
		return;
	if (pChild == pLeaf) {
		BfsData::Accessor nodeData(pChild);
		nodeData.decreaseUnderRunningJobs();
	}
	BfsData::Accessor parentData(pChild->getParent());
	parentData.decreaseUnderRunningJobs();
	restoreUpdateSpecificData(pChild, pLeaf);
}

void BaseBfsHandler::updateRunningJobFlag(NodePtr pNode, bool isRunningJob)
{
	BfsData::Accessor nodeData(pNode);
	nodeData.setRunningJob(isRunningJob);
}

void BaseBfsHandler::updateWithFlagPolicy(NodePtr pNode, bool isFlagged)
{
	if (isFlagged)
		updateFlaggedOn(pNode);
	else
		updateFlaggedOff(pNode);
}

void BaseBfsHandler::updateFlaggedOn(NodePtr pNode)
{
	BfsData::Accessor nodeData(pNode);
	if (nodeData.isFlagged())
		return;
	bool bHasFlaggedChild = false;
	NodePtr pChildSibling = pNode->getChild(0);
	for (; pChildSibling != nullptr; pChildSibling = pChildSibling->getRight()) {
		BfsData::Accessor childSiblingData(pChildSibling);
		// ignore win/lose children
		if (childSiblingData.getWinningStatus() != BfsData::UNKNOWN)
			continue;
		// if at least one child is not flagged, node never set flagged
		if (childSiblingData.isFlagged() == false)
			return;
		else
			bHasFlaggedChild = true;
	}
	// if all child is win/lose, flagged is false
	if (bHasFlaggedChild == false && nodeData.isRunningJob() == false)
		return;
	// otherwise, set flagged true
	nodeData.setFlagged(true);
	if (pNode->hasParent())
		updateFlaggedOn(pNode->getParent());
}

void BaseBfsHandler::updateFlaggedOff(NodePtr pNode)
{
	BfsData::Accessor nodeData(pNode);
	if (nodeData.isFlagged() == false)
		return;
	NodePtr pChildSibling = pNode->getChild(0);
	bool bHasFlaggedChild = false;
	for (; pChildSibling != nullptr; pChildSibling = pChildSibling->getRight()) {
		BfsData::Accessor childSiblingData(pChildSibling);
		if (childSiblingData.getWinningStatus() != BfsData::UNKNOWN)
			continue;
		if (childSiblingData.isFlagged() == true) {
			bHasFlaggedChild = true;
		} else {
			nodeData.setFlagged(false);
			if (pNode->hasParent())
				updateFlaggedOff(pNode->getParent());
			return;
		}
	}
	// if all the child is win/lose, disable parent's flag depends on isRunningJob
	if (bHasFlaggedChild == false)  {
		nodeData.setFlagged(nodeData.isRunningJob());
		if (pNode->hasParent())
			updateFlaggedOff(pNode->getParent());
	}
}

void BaseBfsHandler::proveNodesRetrograde(NodePtr pNode, BaseBfsAlgorithm& baseBfsAlgorithm)
{
	if (pNode->isRoot())
		return;
	NodePtr pParent = pNode->getParent();
	BfsData::Accessor nodeData(pNode);
	BfsData::Accessor parentData(pParent);
	if (nodeData.getWinningStatus() != BfsData::UNKNOWN)
		updateFlaggedOn(pParent);

	if (nodeData.getWinningStatus() == BfsData::UNKNOWN) {
		return;
	} else if (nodeData.getPlayerColor() != 
		static_cast<BfsData::PlayerColor>(nodeData.getWinningStatus())) {
		if (parentData.isRunningJob())
			return;
		bool bSucceeded = baseBfsAlgorithm.delayedExpand(pNode);
		if (bSucceeded || parentData.getStopExpanding() == false)
			return;
		NodePtr pSibling = pParent->getChild(0);
		for (; pSibling != nullptr; pSibling = pSibling->getRight()) {
			BfsData::Accessor siblingData(pSibling);
			if (siblingData.getWinningStatus() != nodeData.getWinningStatus())
				return;
		}
	}
	parentData.setWinningStatus(nodeData.getWinningStatus());
	proveNodesRetrograde(pParent, baseBfsAlgorithm);
}

bool BaseBfsHandler::shouldDelayedExpand(NodePtr pNode)
{
	if (pNode->isRoot())
		return false;

	NodePtr pParent = pNode->getParent();
	BfsData::Accessor parentData(pParent);
	if (parentData.isRunningJob() || parentData.getStopExpanding())
		return false;

	int iCount = 0;
	NodePtr pSibling = pParent->getChild(0);
	for (; pSibling != nullptr; pSibling = pSibling->getRight()) {
		BfsData::Accessor siblingData(pSibling);
		if (siblingData.getWinningStatus() == BfsData::UNKNOWN)
			iCount++;
	}
	return iCount < JobLevelConfigure::g_configure.iDelayedExpansionLimit;
}

}
