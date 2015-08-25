#include "GameHandler.h"
#include "BfsData.h"
#include "GameParser.h"
#include <cassert>

namespace joblevel
{

GameHandler::GameHandler()
{
}

void GameHandler::initializeNode(NodePtr pNode) const
{
	BfsData::Accessor nodeData(pNode);
	if (pNode->isRoot())
		nodeData.setPlayerColor(BfsData::PLAYER_ROOT);
	else
		setBfsPlayerColor(pNode);
}

bool GameHandler::isNodeAlreadyExist(NodePtr pNode, GameParser* pGameParser) const
{
	BaseMovePtr pMove = pGameParser->getMove();
	NodePtr pChild = pNode->getChildWithMove(pMove);
	if (pChild != nullptr) {
		delete pMove;
		return true;
	} else {
		return false;
	}
}

NodePtr GameHandler::generateNode(NodePtr pNode, GameParser* pGameParser) const
{
	BaseMovePtr pMove = pGameParser->getMove();
	NodePtr pChild = pNode->generateChild(pMove);
	setBfsPlayerColor(pChild);
	return pChild;
}

void GameHandler::setupGameData(NodePtr pNode, GameParser* pGameParser) const
{
}

bool GameHandler::handleDuplicateNode(NodePtr pNode) const
{
	return false;
}

}
