#include "UctHandler.h"
#include <cmath>
#include <cassert>
#include "UctParserInterface.h"
#include "UctData.h"
#include "BfsData.h"
#include "JobLevelConfigure.h"
#include "BaseJMsgParser.h"

namespace joblevel
{

UctHandler::UctHandler()
	: BaseBfsHandler(),
	  m_pUctParserInterface(NULL)
{
}

bool UctHandler::setBaseJMsgParser(BaseJMsgParser* pBaseJMsgParser)
{
	m_pUctParserInterface = dynamic_cast<UctParserInterface*>(pBaseJMsgParser);
	if (m_pUctParserInterface == NULL)
		return false;
	return true;
}

NodePtr UctHandler::selectBestChild(NodePtr pParent)
{
	NodePtr pChildSibling = pParent->getChild(0);
	NodePtr pBestChild = nullptr;
	for (; pChildSibling != nullptr; pChildSibling = pChildSibling->getRight()) {
		UctData::Accessor siblingData(pChildSibling);
		BfsData::Accessor siblingBfsData(pChildSibling);
		if (siblingBfsData.isFlagged() == true 
			|| siblingBfsData.getWinningStatus() != BfsData::UNKNOWN)
			continue;
		if (pBestChild == nullptr)
			pBestChild = pChildSibling;
		UctData::Accessor bestData(pBestChild);
		if (bestData.getUcbScore() < siblingData.getUcbScore())
			pBestChild = pChildSibling;
	}
	return pBestChild;
}

void UctHandler::initializeSpecificData(NodePtr pNode)
{
	UctData::Accessor nodeData(pNode);
}

void UctHandler::setupSpecificData(NodePtr pNode, const std::string& sResult)
{
	UctData::Accessor nodeData(pNode);
	nodeData.setMoveCount(1);
	assert(m_pUctParserInterface != NULL);
	nodeData.setWinRate(m_pUctParserInterface->getWinRate(sResult));
}

void UctHandler::updateSpecificData(NodePtr pChild, NodePtr pLeaf, bool isPreUpdate)
{
	assert(pChild->isRoot() == false);
	UctData::Accessor childUctData(pChild);
	UctData::Accessor parentUctData(pChild->getParent());
	if (isPreUpdate) {
		if (pChild == pLeaf)
			childUctData.increasePreUpdateMoveCount();
		parentUctData.increasePreUpdateMoveCount();
	} else {
		parentUctData.decreasePreUpdateMoveCount();
		parentUctData.increaseMoveCount();
		if (pChild != pLeaf) {
			BfsData::Accessor childBfsData(pChild);
			UctData::Accessor leafUctData(pLeaf);
			BfsData::Accessor leafBfsData(pLeaf);
			double dChildWinRate = childUctData.getWinRate();
			int iChildMoveCount = childUctData.getMoveCount();
			double dLeafWinRate = leafUctData.getWinRate();
			if (leafBfsData.getPlayerColor() != childBfsData.getPlayerColor())
				dLeafWinRate = 1.0f - dLeafWinRate;
			dChildWinRate = (dChildWinRate * static_cast<double>(iChildMoveCount - 1) 
				+ dLeafWinRate) / static_cast<double>(iChildMoveCount);
			childUctData.setWinRate(dChildWinRate);
		}
	}
	updateUcbScore(pChild->getParent());
}

void UctHandler::restoreUpdateSpecificData(NodePtr pChild, NodePtr pLeaf)
{
	assert(pChild->isRoot() == false);
	if (pChild == pLeaf) {
		UctData::Accessor nodeData(pChild);
		nodeData.decreasePreUpdateMoveCount();
	}
	UctData::Accessor parentData(pChild->getParent());
	parentData.decreasePreUpdateMoveCount();
	updateUcbScore(pChild->getParent());
}

void UctHandler::updateUcbScore(NodePtr pParent)
{
	UctData::Accessor parentUctData(pParent);
	int iParentMoveCount = parentUctData.getMoveCount() + parentUctData.getPreUpdateMoveCount();
	NodePtr pChildSibling = pParent->getChild(0);
	for (; pChildSibling != nullptr; pChildSibling = pChildSibling->getRight()) {
		UctData::Accessor childUctData(pChildSibling);
		double dChildWinRate = childUctData.getWinRate();
		int iChildMoveCount = childUctData.getMoveCount() + childUctData.getPreUpdateMoveCount();
		if (iParentMoveCount > 1) {
			double& dUcbConstant = JobLevelConfigure::g_configure.dUcbConstant;
			double dUcbScore = dChildWinRate + dUcbConstant * 
				(sqrt(log10(static_cast<double>(iParentMoveCount)) / static_cast<double>(iChildMoveCount)));
			childUctData.setUcbScore(dUcbScore);
		}
	}
}

}
