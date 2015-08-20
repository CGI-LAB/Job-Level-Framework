#ifndef JL_JOBLEVELMANAGER_H
#define JL_JOBLEVELMANAGER_H

#include <string>
#include <map>
#include "JobLevelMiddleware.h"

namespace joblevel
{

class AlgorithmInterface;
class BaseBfsHandler;
class BaseGameHandler;

class JobLevelManager
{
public:
	static JobLevelManager g_jobLevelManager;
	friend class JobLevelMiddleware;
	typedef std::map<std::string, AlgorithmInterface*> AlgorithmMap;
	typedef std::map<std::string, BaseBfsHandler*> BfsHandlerMap;
	typedef std::map<std::string, BaseGameHandler*> GameHandlerMap;

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
};

}

#endif
