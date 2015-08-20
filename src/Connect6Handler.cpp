#include "Connect6Handler.h"
#include <sstream>
#include <vector>
#include "Connect6Move.h"
#include "BfsData.h"
#include "JobLevelConfigure.h"

namespace joblevel 
{

Connect6Handler::Connect6Handler()
	: BaseGameHandler(),
	  m_pConnect6JMsgParser()
{
	setBaseJMsgParser(&m_pConnect6JMsgParser);
}

std::string Connect6Handler::getAppName() const
{
	return JobLevelConfigure::g_configure.sConnect6AppName;
}

std::string Connect6Handler::getAppVersion() const
{
	return JobLevelConfigure::g_configure.sConnect6AppVersion;
}

std::string Connect6Handler::getArgument(NodePtr pNode) const
{
	std::ostringstream oss;
	oss << "-playtsumego " << getPath(pNode)
		<< " -ignore " << getIgnoreMove(pNode);
	return oss.str();
}

std::string Connect6Handler::getPath(NodePtr pNode) const
{
	std::vector<NodePtr> vNodes;
	NodePtr pTraversedNode = pNode;
	// push back until root but exclude root
	while (pTraversedNode->hasParent()) {
		vNodes.push_back(pTraversedNode);
		pTraversedNode = pTraversedNode->getParent();
	}
	std::string sPath("");
	for (std::vector<NodePtr>::reverse_iterator rit = vNodes.rbegin(); rit != vNodes.rend(); ++rit)
		sPath += (*rit)->getMove()->serialize(";");
	return sPath;
}

std::string Connect6Handler::getIgnoreMove(NodePtr pNode) const
{
	std::string sIgnoreMove("");
	NodePtr pChildSibling = pNode->getChild(0);
	for (; pChildSibling != nullptr; pChildSibling = pChildSibling->getRight()) {
		if (pChildSibling != pNode->getChild(0))
			sIgnoreMove += "_";
		sIgnoreMove += pChildSibling->getMove()->serialize(";");
	}
	return sIgnoreMove;
}

void Connect6Handler::setBfsPlayerColor(NodePtr pNode) const
{
	BfsData::Accessor nodeData(pNode);
	// only need use Go move to get color
	GoMovePtr pMove = dynamic_cast<GoMove*>(pNode->getMove());
	nodeData.setPlayerColor(static_cast<BfsData::PlayerColor>(pMove->getColor()));
}

bool Connect6Handler::handleDuplicateNode(NodePtr pNode) const
{
	BfsData::Accessor nodeData(pNode);
	nodeData.setStopExpanding(true);
	return true;
}

} // joblevel