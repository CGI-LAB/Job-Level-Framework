#include "BaseGameHandler.h"
#include "BfsData.h"
#include "BaseJMsgParser.h"
#include <cassert>

namespace joblevel
{

BaseGameHandler::BaseGameHandler()
	: m_pBaseJMsgParser(NULL)
{
}

void BaseGameHandler::setBaseJMsgParser(BaseJMsgParser* pBaseJMsgParser)
{
	m_pBaseJMsgParser = pBaseJMsgParser;
}

BaseJMsgParser* BaseGameHandler::getBaseJMsgParser() const
{
	assert(m_pBaseJMsgParser != NULL);
	return m_pBaseJMsgParser;
}

void BaseGameHandler::initializeNode(NodePtr pNode) const
{
	BfsData::Accessor nodeData(pNode);
	if (pNode->isRoot())
		nodeData.setPlayerColor(BfsData::PLAYER_ROOT);
	else
		setBfsPlayerColor(pNode);
}

bool BaseGameHandler::isNodeAlreadyExist(NodePtr pNode, const std::string& sResult) const
{
	assert(m_pBaseJMsgParser != NULL);
	BaseMovePtr pMove = m_pBaseJMsgParser->getMove(sResult);
	NodePtr pChild = pNode->getChildWithMove(pMove);
	if (pChild != nullptr) {
		delete pMove;
		return true;
	} else {
		return false;
	}
}

NodePtr BaseGameHandler::generateNode(NodePtr pNode, const std::string& sResult) const
{
	assert(m_pBaseJMsgParser != NULL);
	BaseMovePtr pMove = m_pBaseJMsgParser->getMove(sResult);
	return pNode->generateChild(pMove);
}

void BaseGameHandler::setupGameData(NodePtr pNode, const std::string& sResult) const
{
	setBfsPlayerColor(pNode);
	BfsData::Accessor nodeData(pNode);
	BfsData::Accessor parentData(pNode->getParent());
	nodeData.setWinningStatus(m_pBaseJMsgParser->getWinningStatus(sResult));
	if ((nodeData.getWinningStatus() == BfsData::BLACK_WIN 
		&& nodeData.getPlayerColor() == BfsData::PLAYER_WHITE)
		|| (nodeData.getWinningStatus() == BfsData::WHITE_WIN 
		&& nodeData.getPlayerColor() == BfsData::PLAYER_BLACK)) {
		parentData.setStopExpanding(true);
	} else {
		parentData.setStopExpanding(m_pBaseJMsgParser->getStopExpanding(sResult));
	}
}

bool BaseGameHandler::handleDuplicateNode(NodePtr pNode) const
{
	return false;
}

}
