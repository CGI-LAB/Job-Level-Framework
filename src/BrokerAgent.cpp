#include "BrokerAgent.h"
#include <iostream>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "AsyncSocket.h"
#include "JobLevelConfigure.h"

namespace joblevel
{

BrokerAgent::BrokerAgent(std::ostream& os, boost::asio::io_service& ioService)
: BrokerAgentExtension(*this, m_workerManager, m_jobManager),
  m_os(os),
  m_ioService(ioService),
  m_timer(ioService, boost::posix_time::seconds(1)),
  m_jobLevelMiddleware(*this)
{
	cgdg::common::Logger::getInstance().open(JobLevelConfigure::g_configure.sCgdgLogFile);
	cgdg::common::Logger::getInstance().setLevel(JobLevelConfigure::g_configure.iCgdgLogLevel);
}

cgdg::common::SocketInterface* BrokerAgent::makeSocket()
{
	return new AsyncSocket(*this, m_ioService);
}

void BrokerAgent::destroySocket(cgdg::common::SocketInterface* pSocket)
{
	AsyncSocket* pAsyncSocket = dynamic_cast<AsyncSocket*>(pSocket);
	delete pAsyncSocket;
}

void BrokerAgent::connectToBroker(const std::string& sIp, const int& iPort)
{
	cgdg::common::ConnectConfig connectConfig;
	connectConfig.addConnectTarget(sIp, iPort);
	setConnectConfig(connectConfig);
	doFirstTimeConnection();
}

void BrokerAgent::startJobLevel(NodePtr pNode)
{
	if (m_jobLevelMiddleware.isRunningAlgorithm())
		std::cerr << "Error: It is running algorithm now" << std::endl;
	else
		m_jobLevelMiddleware.start(pNode);
}

void BrokerAgent::updateWorkerInfoInterval()
{
	if (isConnected() && isLogin()) {
		updateWorkerInfo();
		m_timer.expires_at(m_timer.expires_at() + boost::posix_time::seconds(1));
		m_timer.async_wait(boost::bind(&BrokerAgent::updateWorkerInfoInterval, this));
	}
}

// handlers

void BrokerAgent::handleAuthResult(const std::string& errorCode, const std::string& message)
{
	BrokerAgentExtension::handleAuthResult(errorCode, message);
	if (errorCode == "001") {
		m_os << "Login CGDG successfully" << std::endl << "> " << std::flush;
	} else {
		m_os << "ERROR: Login CGDG error " << errorCode << ", " 
				  << message << std::endl << "> " << std::flush;
		return;
	}
	
	updateWorkerInfo();
	m_timer.async_wait(boost::bind(&BrokerAgent::updateWorkerInfoInterval, this));
}

void BrokerAgent::handleSelectionResult(const std::string& errorCode, const std::string& message, const std::vector<int>& workerList)
{
	BrokerAgentExtension::handleSelectionResult(errorCode, message, workerList);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) 
		m_os << "EVENT: handleSelectionResult" << std::endl << "> " << std::flush;
}

void BrokerAgent::handleJobMsg(int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage)
{
	BrokerAgentExtension::handleJobMsg(iJId, iWId, applicationName, applicationVersion, jobMessage);
	m_jobLevelMiddleware.receiveJobMessage(iJId, jobMessage);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) {
		m_os << "EVENT: handleJobMsg: JID[" << iJId << "] WID[" 
				  << iWId << "] APP[" << applicationName << "] VERSION[" 
				  << applicationVersion << "] MSG[" << jobMessage << "]" 
				  << std::endl << "> " << std::flush;
	}
}

void BrokerAgent::handleSubmissionResult(int iJId, const std::string& errorCode, const std::string& message)
{
	BrokerAgentExtension::handleSubmissionResult(iJId, errorCode, message);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) {
		m_os << "EVENT: handleSubmissionResult: JID[" << iJId << "], " 
				  << errorCode << ", " << message << std::endl << "> " << std::flush;
	}
}

void BrokerAgent::handleJobSendingAvaliable()
{
	BrokerAgentExtension::handleJobSendingAvaliable();
	m_jobLevelMiddleware.requestJobs();
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) 
		m_os << "EVENT: handleJobSendingAvaliable" << std::endl << "> " << std::flush;
}

void BrokerAgent::handleJobDone(int iJId, int iWId, const std::string& sTime, const std::string& uTime, const std::string& kTime)
{
	BrokerAgentExtension::handleJobDone(iJId, iWId, sTime, uTime, kTime);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) {
		m_os << "EVENT: handleJobDone: JID[" << iJId << "] WID[" 
				  << iWId << "] sTime: " << sTime << ", uTime: " << uTime  
				  << ", kTime: " << kTime << std::endl << "> " << std::flush;
	}
}

void BrokerAgent::handleJobFail(int iJId, int iWId)
{
	BrokerAgentExtension::handleJobFail(iJId, iWId);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) {
		m_os << "EVENT: handleJobFail: JID[" << iJId << "] WID[" 
				  << iWId << "]" << std::endl << "> " << std::flush;
	}
}

void BrokerAgent::handleJobDoing(int iJId, int iWId)
{
	BrokerAgentExtension::handleJobDoing(iJId, iWId);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) {
		m_os << "EVENT: handleJobDoing: JID[" << iJId << "] WID[" 
				  << iWId << "]" << std::endl << "> " << std::flush;
	}
}

void BrokerAgent::handleJobAssignDone(int iJId)
{
	BrokerAgentExtension::handleJobAssignDone(iJId);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent)
		m_os << "EVENT: handleJobAssignDone: JID[" << iJId << "]" << std::endl << "> " << std::flush;
}

void BrokerAgent::handleWorkerLost(int iWId)
{
	BrokerAgentExtension::handleWorkerLost(iWId);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent)
		m_os << "EVENT: handleWorkerLost: WID[" << iWId << "]" << std::endl << "> " << std::flush;
}

void BrokerAgent::handleWorkerInfo(const cgdg::client::WorkerStatus& workerStatus)
{
	BrokerAgentExtension::handleWorkerInfo(workerStatus);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) {
		static size_t iWorkerNum = 0;
		if (++iWorkerNum % getWorkerManager().getWorkerList().size() == 0) {
			m_os << "EVENT: handleWorkerInfo" << std::endl << "> " << std::flush;
			iWorkerNum = 0;
		}
	}
}

void BrokerAgent::handleUnknown(const std::string& commandXmlString)
{
	BrokerAgentExtension::handleUnknown(commandXmlString);
	if (JobLevelConfigure::g_configure.bShowBrokerEvent) {
		m_os << "EVENT: handleUnknown" << std::endl << "> " << std::flush;
		m_os << "UNKNOWN: {" << std::endl << "> " << std::flush;
		m_os << commandXmlString << std::endl << "> " << std::flush;
		m_os << "}" << std::endl << "> " << std::flush;
	}
}

void BrokerAgent::handleFirstTimeConnection()
{
	BrokerAgentExtension::handleFirstTimeConnection();
	m_os << "Connect to broker successfully" << std::endl << "> " << std::flush;

	if (JobLevelConfigure::g_configure.bAutoLoginCgdg) {
		login(JobLevelConfigure::g_configure.sCgdgLoginAccount, 
			JobLevelConfigure::g_configure.sCgdgLoginPassword, "");
	}
}

void BrokerAgent::handleConnectionFail()
{
	BrokerAgentExtension::handleConnectionFail();
	m_os << "EVENT: Connect to broker failed" << std::endl << "> " << std::flush;
}

void BrokerAgent::handleConnectionDown()
{
	BrokerAgentExtension::handleConnectionDown();
	m_os << "EVENT: Disconnect to broker " << std::endl << "> " << std::flush;
}

}