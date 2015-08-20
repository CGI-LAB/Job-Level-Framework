#ifndef JL_SEARCHTREECOMMANDS_H
#define JL_SEARCHTREECOMMANDS_H

#include <string>
#include <vector>
#include <ostream>
#include "SearchTreeBrowser.h"

namespace joblevel
{

class CommandsEngine;
class SearchTree;

class SearchTreeCommands
{
public:
	SearchTreeCommands(std::ostream& os, 
		CommandsEngine& commandsEngine, SearchTree& searchTree);
	void cmdStartBrowserMode();

protected:
	// commands
	void cmdShowCurrentNode();
	void cmdMoveCurrentNode();
	void cmdExpandCurrentNode();
	void cmdExpandCurrentNodeInConnect6();
	void cmdDeleteChildOfCurrentNode();
	void cmdSerializeTree();
	void cmdSaveSgfFile();

private:
	std::ostream& m_os;
	std::vector<std::string>& m_vArgs;
	SearchTree& m_searchTree;
	SearchTreeBrowser m_searchTreeBrowser;
};

}

#endif
