#ifndef JL_JOBLEVELCOMMANDS_H
#define JL_JOBLEVELCOMMANDS_H

#include <iostream>
#include <vector>
#include <string>

namespace joblevel
{

class CommandsEngine;
class BrokerAgent;
class SearchTree;

class JobLevelCommands
{
public:
	JobLevelCommands(std::ostream& os, CommandsEngine& commandsEngine, 
		BrokerAgent& brokerAgent, SearchTree& searchTree);

protected:
	// commands
	void cmdConnectToBroker();
	void cmdLoginCgdg();
	void cmdRunJobLevel();

private:
	std::ostream& m_os;
	std::vector<std::string>& m_vArgs;
	BrokerAgent& m_brokerAgent;
	SearchTree& m_searchTree;
};

}

#endif