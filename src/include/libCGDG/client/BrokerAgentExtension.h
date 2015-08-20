#ifndef CLIENT_BROKERAGENTEXTENSION_H
#define CLIENT_BROKERAGENTEXTENSION_H

#include "common/EndTemplate.h"
#include "client/BrokerAgent.h"
#include "client/HandlerInterface.h"
#include "client/OperationInterfaceExtension.h"
#include "client/JobManager.h"
#include "client/WorkerManager.h"

namespace cgdg
{
	namespace client
	{

class BrokerAgentExtension : public common::EndTemplate<HandlerInterface, BrokerAgent>, public HandlerInterface, public OperationInterfaceExtension
{
private:
	bool m_bJobSendingAvailable;
	JobManager& m_aliasJobManager;
	WorkerManager& m_aliasWorkerManager;
	int submitOneJobInQueue();

public:
	BrokerAgentExtension(common::SocketFactoryInterface& aliasSocketFactory, WorkerManager& aliasWorkerManager, JobManager& aliasJobManager);
	
	////////////////
	/// handler ////
	////////////////
	
	//client handler
	virtual void handleAuthResult(const std::string& errorCode, const std::string& message);
	virtual void handleSelectionResult(const std::string& errorCode, const std::string& message, const std::vector<int>& workerList);
	virtual void handleWorkerLost(int iWId);
	virtual void handleWorkerInfo(const WorkerStatus& workerStatus);
	virtual void handleUnknown(const std::string& commandXmlString);
	//common handler
	virtual void handleInitConnect(const std::string& host, unsigned short port);
	virtual void handleHeartBeat();
	virtual void handleFirstTimeConnection();
	virtual void handleReconnection();
	virtual void handleConnectionFail();
	virtual void handleConnectionDown();
	virtual void handleSameSessionId();
	virtual void handleSessionIdChanged();
	//job handler
	virtual void handleSubmissionResult(int iJId, const std::string& errorCode, const std::string& message);
	virtual void handleJobSendingAvaliable();
	virtual void handleJobMsg(int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage);
	virtual void handleJobDone(int iJId, int iWId, const std::string& sTime, const std::string& uTime, const std::string& kTime);
	virtual void handleJobFail(int iJId, int iWId);
	virtual void handleJobDrop(int iJId, int iWId);
	virtual void handleJobDoing(int iJId, int iWId);
	virtual void handleJobAssignDone(int iJId);
	virtual void handleJobAbortAck(int iJId, int iWId, const std::string& errorCode, const std::string& message);
	//unknown handler
	virtual void handleRecheckIn(bool bIsNewBroker);
	
	////////////////
	/// Operation //
	////////////////
	
	bool isLogin() const;
	virtual int login(const std::string& userName, const std::string& password, const std::string& description);
	virtual int recheckIn();
	virtual int logout();
	virtual int updateWorkerInfo(const std::vector<int>& iWIds);
	virtual int updateWorkerInfo(const std::string& organization);
	virtual int updateWorkerInfo();
	virtual int selectWorker(const std::vector<int>& targets, int prioirty, int nMaxCore);
	virtual int selectWorker(const std::vector<Filter>& filters, int prioirty);
	virtual int submitJob(const std::string& applicationName, const std::string& applicationVersion, int m_iPrioirty, const std::string& argument, int nCores = 1, bool bIsAbortable = false, const std::string& averageTime = "", const std::string& maxTime = "");
	virtual int abortJob(int iJId);
	virtual int sendJobinput(int iJId, const std::string& jobInput);

	//getter
	JobManager& getJobManager();
	const JobManager& getJobManager() const;
	WorkerManager& getWorkerManager();
	const WorkerManager& getWorkerManager() const;
};

inline bool BrokerAgentExtension::isLogin() const
{
	return m_brokerAgent.isLogin();
}

inline int BrokerAgentExtension::login(const std::string& userName, const std::string& password, const std::string& description)
{
	return m_brokerAgent.login(userName, password, description);
}

inline int BrokerAgentExtension::recheckIn()
{
	return m_brokerAgent.recheckIn();
}

inline int BrokerAgentExtension::logout()
{
	getWorkerManager().clear();
	getJobManager().clear();
	return m_brokerAgent.logout();
}

inline int BrokerAgentExtension::updateWorkerInfo(const std::vector<int>& iWIds)
{
	return m_brokerAgent.updateWorkerInfo(iWIds);
}

inline int BrokerAgentExtension::updateWorkerInfo(const std::string& organization)
{
	return m_brokerAgent.updateWorkerInfo(organization);
}

inline int BrokerAgentExtension::updateWorkerInfo()
{
	return m_brokerAgent.updateWorkerInfo();
}

inline int BrokerAgentExtension::selectWorker(const std::vector<int>& targets, int iPrioirty, int nMaxCore)
{
	return m_brokerAgent.selectWorker(targets, iPrioirty, nMaxCore);
}

inline int BrokerAgentExtension::selectWorker(const std::vector<Filter>& filters, int iPrioirty)
{
	return m_brokerAgent.selectWorker(filters, iPrioirty);
}

inline int BrokerAgentExtension::abortJob(int iJId)
{
	//getJobManager().updateJobStatus(iJId, JOBSTATUS_ABORT);
	return m_brokerAgent.abortJob(iJId);
}

inline int BrokerAgentExtension::sendJobinput(int iJId, const std::string& jobInput)
{
	return m_brokerAgent.sendJobinput(iJId, jobInput);
}

inline JobManager& BrokerAgentExtension::getJobManager()
{
	return m_aliasJobManager;
}

inline const JobManager& BrokerAgentExtension::getJobManager() const
{
	return m_aliasJobManager;
}

inline WorkerManager& BrokerAgentExtension::getWorkerManager()
{
	return m_aliasWorkerManager;
}

inline const WorkerManager& BrokerAgentExtension::getWorkerManager() const
{
	return m_aliasWorkerManager;
}

	}
}

#endif
