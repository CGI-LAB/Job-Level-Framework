#include "JobLevelMiddleware.h"
#include <iostream>
#include <cassert>
#include <sstream>
#include "BrokerAgent.h"
#include "AlgorithmInterface.h"
#include "JobLevelConfigure.h"
#include "JobLevelManager.h"

namespace joblevel
{

JobLevelMiddleware::JobLevelMiddleware(BrokerAgent& brokerAgent)
	: m_brokerAgent(brokerAgent),
	  m_bJobSendingAvalible(false),
	  m_pAlgorithm(NULL),
	  m_isRunningAlgorithm(false)
{
}

void JobLevelMiddleware::start(NodePtr pNode)
{
	AlgorithmInterface* pAlgorithm = JobLevelManager::g_jobLevelManager.getAlgorithm();
	if (pAlgorithm == NULL)
		return;
	setAlgorithm(pAlgorithm);
	m_isRunningAlgorithm = true;
	assert(m_pAlgorithm != NULL);
	std::cout << "Start running job-level algorithm" << std::endl;
	if (m_pAlgorithm->initialize(pNode) == false)
		return;
	requestJobs();
}

void JobLevelMiddleware::stop()
{
	m_isRunningAlgorithm = false;
}

bool JobLevelMiddleware::isRunningAlgorithm() const
{
	return m_isRunningAlgorithm;
}

void JobLevelMiddleware::setAlgorithm(AlgorithmInterface* pAlgorithm)
{
	m_pAlgorithm = pAlgorithm;
	assert(m_pAlgorithm != NULL);
	m_pAlgorithm->setJobLevelMiddleware(this);
}

AlgorithmInterface* JobLevelMiddleware::getAlgorithm() const
{
	assert(m_pAlgorithm != NULL);
	return m_pAlgorithm;
}

void JobLevelMiddleware::requestJobs()
{	
	if (m_isRunningAlgorithm == false)
		return;
	assert(m_pAlgorithm != NULL);
	bool bSuceeded = m_pAlgorithm->requestJobs();
	// If sending job doesn't success, set sending avalible true 
	// for requesting job after received message. 
	m_bJobSendingAvalible = !bSuceeded;
}

void JobLevelMiddleware::receiveJobMessage(int iJId, const std::string& sMessage)
{
	if (m_jIdNodeMap.find(iJId) == m_jIdNodeMap.end()) {
		std::cerr << "Error: Receive message with unknown JID: " 
				  << iJId << std::endl << "> " << std::flush;
		return;
	}

	NodePtr pNode = m_jIdNodeMap[iJId];
	assert(m_pAlgorithm != NULL);
	m_pAlgorithm->receiveJobMessage(iJId, pNode, sMessage);
	m_jIdNodeMap.erase(iJId);

	bool isAlgorithmCompleted = m_pAlgorithm->isCompleted();
	if (!isAlgorithmCompleted && m_bJobSendingAvalible) {
		requestJobs();
	} else if (isAlgorithmCompleted) {
		stop();
		if (m_jIdNodeMap.empty())
			m_pAlgorithm->finalize();
	}
}

int JobLevelMiddleware::submitJob(NodePtr pNode, const std::string& sApplicationName,
	const std::string& sApplicationVersion, const std::string& sArgument)
{
	int iJId = m_brokerAgent.submitJob(sApplicationName, sApplicationVersion,
		JobLevelConfigure::g_configure.iJobPriority, sArgument,
		JobLevelConfigure::g_configure.nJobCores,
		JobLevelConfigure::g_configure.bJobIsAbortable,
		JobLevelConfigure::g_configure.sJobAverageTime,
		JobLevelConfigure::g_configure.sJobMaxTime);
	m_jIdNodeMap[iJId] = pNode;

	return iJId;
}

int JobLevelMiddleware::sendJobinput(NodePtr pNode, int iJId, const std::string& sJobInput)
{
	int error = m_brokerAgent.sendJobinput(iJId, sJobInput);
	if (!error)
		m_jIdNodeMap[iJId] = pNode;

	std::ostringstream oss;
	oss << "Send job ID " << iJId << " input: " << sJobInput << std::endl;
	pNode->appendComment(oss.str());

	return error;
}

int JobLevelMiddleware::abortJob(int iJId)
{
	return m_brokerAgent.abortJob(iJId);
}

bool JobLevelMiddleware::hasWaitingJob()
{
	return m_brokerAgent.getJobManager().hasWaitingJob();
}

}
