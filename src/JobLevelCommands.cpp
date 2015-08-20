#include "JobLevelCommands.h"
#include <sstream>
#include "CommandsEngine.h"
#include "BrokerAgent.h"
#include "JobLevelConfigure.h"
#include "SearchTree.h"

namespace joblevel
{

JobLevelCommands::JobLevelCommands(std::ostream& os, CommandsEngine& commandsEngine, 
	BrokerAgent& brokerAgent, SearchTree& searchTree)
	: m_os(os),
	  m_vArgs(commandsEngine.getArgs()),
	  m_brokerAgent(brokerAgent),
	  m_searchTree(searchTree)
{
	commandsEngine.registerFunction("connect", this, &JobLevelCommands::cmdConnectToBroker, 0, 2);
	commandsEngine.registerFunction("login", this, &JobLevelCommands::cmdLoginCgdg, 0, 2);
	
	commandsEngine.registerFunction("run", this, &JobLevelCommands::cmdRunJobLevel, 0);
}

void JobLevelCommands::cmdConnectToBroker()
{
	if (m_brokerAgent.isConnected()) {
		m_os << "Already connected to broker" << std::endl;
		return;
	}
	std::string sIp = JobLevelConfigure::g_configure.sBrokerIp;
	int iPort = JobLevelConfigure::g_configure.iBrokerPort;
	if (m_vArgs.size() >= 1)
		sIp = m_vArgs[0];
	if (m_vArgs.size() == 2) {
		std::istringstream iss(m_vArgs[1]);
		iss >> iPort;
	}
	m_brokerAgent.connectToBroker(sIp, iPort);
	m_os << "IP = " << sIp << std::endl
		 << "port = " << iPort << std::endl
		 << "Connect to broker..." << std::endl;
}

void JobLevelCommands::cmdLoginCgdg()
{
	if (!m_brokerAgent.isConnected()) {
		m_os << "Need to connect to broker first" << std::endl;
		return;
	}
	if (m_brokerAgent.isLogin()) {
		m_os << "Already login CGDG" << std::endl;
		return;
	}
	std::string sAccount = JobLevelConfigure::g_configure.sCgdgLoginAccount;
	std::string sPassword = JobLevelConfigure::g_configure.sCgdgLoginPassword;
	if (m_vArgs.size() >= 1)
		sAccount = m_vArgs[0];
	if (m_vArgs.size() == 2)
		sPassword = m_vArgs[1];
	m_brokerAgent.login(sAccount, sPassword, "");
	m_os << "User = " << sAccount << std::endl
		 << "Login CGDG..." << std::endl;
}

void JobLevelCommands::cmdRunJobLevel()
{
	if (!m_brokerAgent.isLogin()) 
		m_os << "Need to login CGDG" << std::endl;
	else
		m_brokerAgent.startJobLevel(m_searchTree.getCurrentNode());
}

}
