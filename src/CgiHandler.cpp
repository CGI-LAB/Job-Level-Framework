#include "CgiHandler.h"
#include <sstream>
#include <vector>
#include "GoMove.h"
#include "BfsData.h"
#include "JobLevelConfigure.h"

namespace joblevel
{

CgiHandler::CgiHandler()
	: GameHandler(),
	  m_pGoJMsgParser()
{
	setBaseJMsgParser(&m_pGoJMsgParser);
}

std::string CgiHandler::getAppName() const
{
	return JobLevelConfigure::g_configure.sGoAppName;
}

std::string CgiHandler::getAppVersion() const
{
	return JobLevelConfigure::g_configure.sGoAppVersion;
}

std::string CgiHandler::prepareJobCommands(NodePtr pNode) const
{
	std::ostringstream oss;
	oss << "-mode jlmcts -conf_str PATH=" << getPath(pNode);
	std::string sIgnoreMove = getIgnoreMove(pNode);
	if (sIgnoreMove.length() > 0)
		oss	<< ":IGNORE=" << sIgnoreMove;
	oss << ":SIM_CONTROL=MAX_NODECOUNT:SIM_MAXNODE_COUNT_LIMIT="
		<< JobLevelConfigure::g_configure.iGoSimulationLimit;
	return oss.str();
}

std::string CgiHandler::getPath(NodePtr pNode) const
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
		sPath += (*rit)->getMove()->serialize();
	return sPath;
}

std::string CgiHandler::getIgnoreMove(NodePtr pNode) const
{
	std::string sIgnoreMove("");
	NodePtr pChildSibling = pNode->getChild(0);
	for (; pChildSibling != nullptr; pChildSibling = pChildSibling->getRight())
		sIgnoreMove += pChildSibling->getMove()->serialize();
	return sIgnoreMove;
}

void CgiHandler::setBfsPlayerColor(NodePtr pNode) const
{
	BfsData::Accessor nodeData(pNode);
	GoMovePtr pGoMove = dynamic_cast<GoMove*>(pNode->getMove());
	nodeData.setPlayerColor(static_cast<BfsData::PlayerColor>(pGoMove->getColor()));
}

}
