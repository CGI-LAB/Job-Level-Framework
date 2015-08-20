#include "SearchTreeCommands.h"
#include "CommandsEngine.h"
#include "Connect6Move.h"
#include "GoMove.h"
#include "SearchTree.h"
#include "SgfSerializer.h"
#include <sstream>

namespace joblevel
{

SearchTreeCommands::SearchTreeCommands(std::ostream& os, 
	CommandsEngine& commandsEngine, SearchTree& searchTree)
	: m_os(os),
	  m_vArgs(commandsEngine.getArgs()),
	  m_searchTree(searchTree),
	  m_searchTreeBrowser(m_searchTree)
{
	commandsEngine.registerFunction("show", this, &SearchTreeCommands::cmdShowCurrentNode, 0);
	commandsEngine.registerFunction("move", this, &SearchTreeCommands::cmdMoveCurrentNode, 1, 2);
	commandsEngine.registerFunction("expand", this, &SearchTreeCommands::cmdExpandCurrentNode, 1);
	commandsEngine.registerFunction("expand_C6", this, &SearchTreeCommands::cmdExpandCurrentNodeInConnect6, 1);
	commandsEngine.registerFunction("delete", this, &SearchTreeCommands::cmdDeleteChildOfCurrentNode, 1);
	commandsEngine.registerFunction("serialize", this, &SearchTreeCommands::cmdSerializeTree, 0);
	commandsEngine.registerFunction("save", this, &SearchTreeCommands::cmdSaveSgfFile, 1);
}

void SearchTreeCommands::cmdShowCurrentNode()
{
	m_searchTreeBrowser.printNode(m_os, m_searchTree.getCurrentNode());
}

void SearchTreeCommands::cmdStartBrowserMode()
{
	m_searchTreeBrowser.startBrowserMode();
}

void SearchTreeCommands::cmdMoveCurrentNode()
{
	std::istringstream iss;
	size_t index = 0;
	NodePtr pCurrentNode = m_searchTree.getCurrentNode();
	if (m_vArgs[0] == "up") {
		if (pCurrentNode->hasParent()) {
			pCurrentNode = pCurrentNode->getParent();
			m_os << "Move up current node" << std::endl;
		} else {
			m_os << "Current node is root" << std::endl;
		}
	} else if (m_vArgs[0] == "right") {
		if (pCurrentNode->hasRight()) {
			pCurrentNode = pCurrentNode->getRight();
			m_os << "Move right current node" << std::endl;
		} else {
			m_os << "Current node doesn't have right node" << std::endl;
		}
	} else if (m_vArgs[0] == "down") {
		iss.str(m_vArgs[1]);
		iss >> index;
		if (pCurrentNode->hasChild(index)) {
			pCurrentNode = pCurrentNode->getChild(index);
			m_os << "Move down current node" << std::endl;
		} else {
			m_os << "Current node doesn't have child index " << index << std::endl;
		}
	} else if (m_vArgs[0] == "left") {
		if (pCurrentNode->hasLeft()) {
			pCurrentNode = pCurrentNode->getLeft();
			m_os << "Move left current node" << std::endl;
		} else {
			m_os << "Current node doesn't have left node" << std::endl;
		}
	} else {
		m_os << "Arguments error. Usage: move up|right|down <index>|left" << std::endl;
	}
	m_searchTree.setCurrentNode(pCurrentNode);
}

void SearchTreeCommands::cmdExpandCurrentNode()
{
	std::string sPath = m_vArgs[0];
	GoMove::Parser goMoveParser;
	NodePtr pLastNewNode = goMoveParser.expandPath(m_searchTree.getCurrentNode(), sPath);
	m_searchTree.setCurrentNode(pLastNewNode);
	m_os << "Expand move: " << sPath << std::endl;
}

void SearchTreeCommands::cmdExpandCurrentNodeInConnect6()
{
	std::string sPath = m_vArgs[0];
	Connect6Move::Parser connect6MoveParser;
	NodePtr pLastNewNode = connect6MoveParser.expandPath(m_searchTree.getCurrentNode(), sPath);
	m_searchTree.setCurrentNode(pLastNewNode);
	m_os << "Expand move: " << sPath << std::endl;
}

void SearchTreeCommands::cmdDeleteChildOfCurrentNode()
{
	size_t index;
	std::istringstream iss(m_vArgs[0]);
	iss >> index;
	bool bDeleteSuccess = m_searchTree.getCurrentNode()->deleteChild(index);
	if (bDeleteSuccess)
		m_os << "Delete child index " << index << std::endl;
	else
		m_os << "Child index " << index << " doesn't exist" << std::endl;
}

void SearchTreeCommands::cmdSerializeTree()
{
	SgfSerializer s;
	m_os << s.serialize() << std::endl;
}

void SearchTreeCommands::cmdSaveSgfFile()
{
	std::string sFileName = m_vArgs[0];
	bool bSuceeded = m_searchTree.saveSgfFile(sFileName);
	if (bSuceeded) {
		m_os << "Save SGF to file " << sFileName << " successfully" << std::endl;
	}
	else {
		m_os << "Error: Unable to open file " << sFileName
			 << " to write" << std::endl;
	} 
}

}
