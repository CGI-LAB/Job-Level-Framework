#ifndef JL_JOBLEVELMANAGER_H
#define JL_JOBLEVELMANAGER_H

#include <string>
#include <map>
#include <utility>
#include "JobLevelMiddleware.h"

namespace joblevel
{

class AlgorithmInterface;
class BfsHandler;
class GameHandler;
class Integrator;

class JobLevelManager
{
public:
	static JobLevelManager g_jobLevelManager;
	friend class JobLevelMiddleware;
	typedef std::map<std::string, AlgorithmInterface*> AlgorithmMap;
	typedef std::map<std::string, BfsHandler*> BfsHandlerMap;
	typedef std::map<std::string, GameHandler*> GameHandlerMap;
	typedef std::map<std::pair<std::string, std::string>, Integrator*> IntegratorMap;

public:
	~JobLevelManager();

private:
	JobLevelManager();
	JobLevelManager(const JobLevelManager&);
	JobLevelManager& operator=(const JobLevelManager&);
	void setupMap();
	AlgorithmInterface* getAlgorithm();

private:
	AlgorithmMap m_algorithms;
	BfsHandlerMap m_bfsHandlers;
	GameHandlerMap m_gameHandlers;
	IntegratorMap m_integrators;
};

}

#endif
