#ifndef JL_JOBLEVELMIDDLEWARE_H
#define JL_JOBLEVELMIDDLEWARE_H

#include <map>
#include <string>
#include "Node.h"

namespace joblevel
{

class BrokerAgent;
class AlgorithmInterface;

class JobLevelMiddleware
{
public:
	JobLevelMiddleware(BrokerAgent& brokerAgent);
	void setAlgorithm(AlgorithmInterface* pAlgorithm);
	AlgorithmInterface* getAlgorithm() const;
	void start(NodePtr pNode);
	void stop();
	bool isRunningAlgorithm() const;
	void requestJobs();
	void receiveJobMessage(int iJId, const std::string& sMessage);
	int submitJob(NodePtr pNode, const std::string& sApplicationName,
		const std::string& sApplicationVersion, const std::string& sArgument);
	int sendJobinput(NodePtr pNode, int iJId, const std::string& sJobInput);
	int abortJob(int iJId);
	bool hasWaitingJob();
private:
	BrokerAgent& m_brokerAgent;
	bool m_bJobSendingAvalible;
	std::map<int, NodePtr> m_jIdNodeMap;
	AlgorithmInterface* m_pAlgorithm;
	bool m_isRunningAlgorithm;
};

}

#endif
