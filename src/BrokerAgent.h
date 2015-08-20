#ifndef JL_BROKERAGENT_H
#define JL_BROKERAGENT_H

#include <client/BrokerAgentExtension.h>
#include <common/SocketFactoryInterface.h>
#include <boost/asio.hpp>
#include <iostream>
#include "JobLevelMiddleware.h"
#include "Node.h"

namespace joblevel 
{

class BrokerAgent
	: public cgdg::client::BrokerAgentExtension,
	  public cgdg::common::SocketFactoryInterface
{
public:
	BrokerAgent(std::ostream& os, boost::asio::io_service& ioService);
	
	cgdg::common::SocketInterface* makeSocket();
	void destroySocket(cgdg::common::SocketInterface* pSocket);

	void connectToBroker(const std::string& sIp, const int& iPort);
	void startJobLevel(NodePtr pNode);

	virtual void handleAuthResult(const std::string& errorCode, const std::string& message);
	virtual void handleSelectionResult(const std::string& errorCode, const std::string& message, const std::vector<int>& workerList);
	virtual void handleSubmissionResult(int iJId, const std::string& errorCode, const std::string& message);

	virtual void handleJobSendingAvaliable();
	virtual void handleJobMsg(int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage);

	virtual void handleJobDone(int iJId, int iWId, const std::string& sTime, const std::string& uTime, const std::string& kTime);
	virtual void handleJobFail(int iJId, int iWId);
	virtual void handleJobDoing(int iJId, int iWId);
	virtual void handleJobAssignDone(int iJId);

	virtual void handleWorkerLost(int iWId);
	virtual void handleWorkerInfo(const cgdg::client::WorkerStatus& workerStatus);

	virtual void handleUnknown(const std::string& commandXmlString);

	virtual void handleFirstTimeConnection();
	virtual void handleConnectionFail();
	virtual void handleConnectionDown();

private:
	void updateWorkerInfoInterval();

private:
	std::ostream& m_os;
	cgdg::client::WorkerManager m_workerManager;
	cgdg::client::JobManager m_jobManager;
	boost::asio::io_service& m_ioService;
	boost::asio::deadline_timer m_timer;
	JobLevelMiddleware m_jobLevelMiddleware;
};

}

#endif
