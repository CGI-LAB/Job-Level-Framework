#include "JobLevelManager.h"
#include <iostream>
#include "JobLevelConfigure.h"
#include "CommonBfJlModules.h"
#include "UctHandler.h"
#include "MiniMaxHandler.h"
#include "CgiHandler.h"
#include "Nctu6Handler.h"

namespace joblevel
{

JobLevelManager JobLevelManager::g_jobLevelManager;

void JobLevelManager::setupMap()
{
	JobLevelConfigure& cf = JobLevelConfigure::g_configure;
	// register algorithms
	m_algorithms[cf.sBfsAlgorithmType] = new CommonBfJlModules;

	// register BFS handlers
	m_bfsHandlers[cf.sUctHandlerType] = new UctHandler;
	m_bfsHandlers[cf.sMiniMaxHandlerType] = new MiniMaxHandler;

	// register Game handlers
	m_gameHandlers[cf.sGoGameType] = new CgiHandler;
	m_gameHandlers[cf.sConnect6GameType] = new Nctu6Handler;
}

AlgorithmInterface* JobLevelManager::getAlgorithm()
{
	std::string& sAlgorithmType = JobLevelConfigure::g_configure.sAlgorithmType;
	if (m_algorithms.find(sAlgorithmType) == m_algorithms.end()) {
		std::cerr << "Can't find algorithm: " << sAlgorithmType << std::endl;
		return NULL;
	} 

	if (sAlgorithmType == JobLevelConfigure::g_configure.sBfsAlgorithmType) {	
		std::string& sBfsHandlerType = JobLevelConfigure::g_configure.sBfsHandlerType;
		std::string& sGameType = JobLevelConfigure::g_configure.sGameType;

		if (m_bfsHandlers.find(sBfsHandlerType) == m_bfsHandlers.end()) {
			std::cerr << "Can't find BFS handler: " << sBfsHandlerType << std::endl;
			return NULL;
		} else if (m_gameHandlers.find(sGameType) == m_gameHandlers.end()) {
			std::cerr << "Can't find Game handler: " << sGameType << std::endl;
			return NULL;
		}
		if (m_bfsHandlers[sBfsHandlerType]->setBaseJMsgParser(
			m_gameHandlers[sGameType]->getBaseJMsgParser()) == false) {
			std::cerr << sGameType << " doesn't support " << sBfsHandlerType << std::endl;
			return NULL;
		}
		dynamic_cast<CommonBfJlModules*>(m_algorithms[sAlgorithmType])
			->setBfsHandler(m_bfsHandlers[sBfsHandlerType]);
		dynamic_cast<CommonBfJlModules*>(m_algorithms[sAlgorithmType])
			->setGameHandler(m_gameHandlers[sGameType]);
	}

	return m_algorithms[sAlgorithmType];
}

JobLevelManager::JobLevelManager()
{
	setupMap();
}

JobLevelManager::~JobLevelManager()
{
	for (JobLevelManager::AlgorithmMap::iterator it = m_algorithms.begin(); it != m_algorithms.end(); ++it)
		delete (it->second);
	for (JobLevelManager::BfsHandlerMap::iterator it = m_bfsHandlers.begin(); it != m_bfsHandlers.end(); ++it)
		delete (it->second);
	for (JobLevelManager::GameHandlerMap::iterator it = m_gameHandlers.begin(); it != m_gameHandlers.end(); ++it)
		delete (it->second);
}

}