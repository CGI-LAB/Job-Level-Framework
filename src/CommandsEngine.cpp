#include "CommandsEngine.h"
#include <sstream>
#include <cassert>

namespace joblevel
{

CommandsEngine::Entry::Entry(std::string key, FuncPtr fp, size_t nMinArgc, size_t nMaxArgc)
	: m_key(key), m_fp(fp), m_nMinArgc(nMinArgc), m_nMaxArgc(nMaxArgc)
{
}

size_t CommandsEngine::Entry::getMinArgc() const
{
	return m_nMinArgc;
}

size_t CommandsEngine::Entry::getMaxArgc() const
{
	return m_nMaxArgc;
}

const std::string& CommandsEngine::Entry::getKey() const
{
	return m_key;
}

CommandsEngine::FuncPtr CommandsEngine::Entry::getFunction() const
{
	return m_fp;
}

bool CommandsEngine::Entry::operator<(const Entry& rhs) const
{
	return m_key < rhs.m_key;
}

CommandsEngine::CommandsEngine(std::ostream& os)
	: m_os(os), m_isQuit(false)
{
	registerFunction("list_command", this, &CommandsEngine::cmdListCommands, 0);
	registerFunction("known_command", this, &CommandsEngine::cmdKnownCommand, 1);
	registerFunction("quit", this, &CommandsEngine::cmdQuit, 0);
	registerFunction("exit", this, &CommandsEngine::cmdQuit, 0);
}

void CommandsEngine::cmdListCommands()
{
	std::map<std::string, Entry>::iterator it;
	for (it = m_mapFunction.begin(); it != m_mapFunction.end(); ++it) {
		m_os << it->first << std::endl;
	}
}

void CommandsEngine::cmdKnownCommand()
{
	m_os << ((m_mapFunction.find(m_vArgs[0]) != m_mapFunction.end()) ? "true" : "false") 
		 << std::endl;
}

void CommandsEngine::cmdDefault()
{
	m_os << "unknown command" << std::endl;
}

void CommandsEngine::cmdQuit()
{
	m_isQuit = true;
}

bool CommandsEngine::hasQuit() const
{
	return m_isQuit;
}

std::vector<std::string>& CommandsEngine::getArgs()
{
	return m_vArgs;
}

void CommandsEngine::runCommand(const std::string& sCommandLine)
{
	m_sCommand.clear();
	m_vArgs.clear();
	m_sCommandLine = sCommandLine;

	std::istringstream iss(sCommandLine);

	iss >> m_sCommand >> std::ws;
	if (m_sCommand.length() == 0) {
		return;
	}

	std::string arg;
	while (iss >> arg) {
		m_vArgs.push_back(arg);
	} 

	std::map<std::string, Entry>::iterator it = m_mapFunction.find(m_sCommand);

	if (it == m_mapFunction.end()) {
		cmdDefault();
	} else {
		Entry* entry = &(it->second);
		if (!checkArgSize(entry))
			return;
		FuncPtr fp = entry->getFunction();
		(*fp)();
	}
}

bool CommandsEngine::checkArgSize(const Entry* pEntry)
{
	size_t nArgsSize = m_vArgs.size();
	size_t upper = pEntry->getMaxArgc();
	size_t lower = pEntry->getMinArgc();
	if (nArgsSize < lower || nArgsSize > upper) {
		m_os << "command needs ";
		if (lower == upper) {
			m_os << "exactly " << lower << " argument" << (lower == 1 ? "" : "s") << std::endl;
		} else {
			m_os << lower << " to " << upper << " arguments" << std::endl;
		}
		return false;
	} else {
		return true;
	}
}

std::vector<std::string> CommandsEngine::getCompleters()
{
	std::vector<std::string> vCompleters;
	std::map<std::string, Entry>::iterator it;
	for (it = m_mapFunction.begin(); it != m_mapFunction.end(); ++it)
		vCompleters.push_back(it->first);
	return vCompleters;
}

}
