#ifndef WORKER_BROKERAGENTEXTENSION_H
#define WORKER_BROKERAGENTEXTENSION_H

#include "common/EndTemplate.h"
#include "worker/BrokerAgent.h"
#include "worker/HandlerInterface.h"
#include "worker/OperationInterface.h"

namespace cgdg
{
	namespace worker
	{

class BrokerAgentExtension : public common::EndTemplate<HandlerInterface, BrokerAgent>, public HandlerInterface, public OperationInterface
{
public:
	BrokerAgentExtension(common::SocketFactoryInterface& aliasSocketFactory);

	bool isCheckedIn() const;

	virtual void handleInitWorker(const std::string& brokerVersion, const std::string& workerVersion);

	virtual void handleJAssign(int iUId, int iJId, const std::string& applicationName, const std::string& applicationVersion, int nCore, const std::string& argument);
	virtual void handleJAbort(int iUId, int iJId);
	virtual void handleJIn(int iUId, int iJId, const std::string& jobInput);

	virtual void handleInitDaemon(const std::string& daemonRatio);
	virtual void handleUpdateWorker(const std::string& workerVersion, const std::string brokerHost, unsigned short brokerPort,
	                                const std::string& organization, int nCore, const std::string& fileServer, const std::string& brokerList);
	virtual void handleJSetCore(int iUId, int iJId, int iWId, int iCore, int iSetCore);
	virtual void handleJSetCoreAck(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& serrorCode, const std::string& sMessage);
	virtual void handleUnknown(const std::string& commandXmlString);

	virtual void handleInitConnect(const std::string& host, unsigned short port);
	virtual void handleHeartBeat();
	virtual void handleFirstTimeConnection();
	virtual void handleReconnection();
	virtual void handleConnectionFail();
	virtual void handleConnectionDown();
	virtual void handleSameSessionId();
	virtual void handleSessionIdChanged();

	virtual int checkIn(const std::string& workerVersion, int nCore, const std::string& internalIp, const std::string& hostName,
	                    const std::string& os, const std::string& organization, const std::string& description, const std::string& fileServer, const std::string& brokerList, const std::string& inops, const std::string& flops);
	virtual int recheckIn();
	virtual int checkOut();
	virtual int sendAlive(
		int nCoreNum,
		int nCoreUsed,
		unsigned cpuSpeed, // in MHz
		unsigned cpuUsage, // in %
		unsigned ramSize, // in MB
		unsigned ramUsage, // in %
		double inops, // in operations/second
		double flops // in operations/second
	);
	virtual int sendJobDoing(int iUId, int iJId);
	virtual int sendJobMessage(int iUId, int iJId, const std::string& applicationName,
	                           const std::string& applicationVersion, const std::string& jobMessage);
	virtual int sendJobFail(int iUId, int iJId, const std::string& errorCode, const std::string& message);
	virtual int sendJobDone(int iUId, int iJId, const std::string& uTime, const std::string& kTime);
	virtual int sendJobAbortAck(int iUId, int iJId, const std::string& errorCode, const std::string& message);

	virtual int sendSleep();
	virtual int sendWakeUp();
	virtual int sendUpdateWorkerAck(const std::string& errorCode, const std::string& message);
	virtual int sendJSetCore(int iUId, int iJId, int iWId, int iCore, int iSetCore);
	virtual int sendJSetCoreAck(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& sErrorCode, const std::string& sMessage);
};

inline BrokerAgentExtension::BrokerAgentExtension(common::SocketFactoryInterface& aliasSocketFactory) : 
common::EndTemplate<HandlerInterface, BrokerAgent>(aliasSocketFactory)
{
	setHandler(this);
}

inline bool BrokerAgentExtension::isCheckedIn() const
{
	return m_brokerAgent.isCheckedIn();
}

inline void BrokerAgentExtension::handleInitWorker(const std::string& brokerVersion, const std::string& workerVersion)
{
}

inline void BrokerAgentExtension::handleJAssign(int iUId, int iJId, const std::string& applicationName, const std::string& applicationVersion, int nCore, const std::string& argument)
{
}

inline void BrokerAgentExtension::handleJAbort(int iUId, int iJId)
{
}

inline void BrokerAgentExtension::handleJIn(int iUId, int iJId, const std::string& jobInput)
{
}

inline void BrokerAgentExtension::handleInitDaemon(const std::string& daemonRatio)
{
}

inline void BrokerAgentExtension::handleUpdateWorker(const std::string& workerVersion, const std::string brokerHost, unsigned short brokerPort,
													 const std::string& organization, int nCore, const std::string& fileServer, const std::string& brokerList)
{
}

inline void BrokerAgentExtension::handleJSetCore(int iUId, int iJId, int iWId, int iCore, int iSetCore)
{
}

inline void BrokerAgentExtension::handleJSetCoreAck(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& serrorCode, const std::string& sMessage)
{
}

inline void BrokerAgentExtension::handleUnknown(const std::string& commandXmlString)
{
}

inline void BrokerAgentExtension::handleInitConnect(const std::string& host, unsigned short port)
{
	m_connectHelper.doDemandConnection(host, port);
}

inline void BrokerAgentExtension::handleHeartBeat()
{
}

inline void BrokerAgentExtension::handleFirstTimeConnection()
{
}

inline void BrokerAgentExtension::handleReconnection()
{
	recheckIn();
}

inline void BrokerAgentExtension::handleConnectionFail()
{
}

inline void BrokerAgentExtension::handleConnectionDown()
{
}

inline void BrokerAgentExtension::handleSameSessionId()
{
}

inline void BrokerAgentExtension::handleSessionIdChanged()
{
}

inline int BrokerAgentExtension::checkIn(const std::string& workerVersion, int nCore, const std::string& internalIp, const std::string& hostName,
                                         const std::string& os, const std::string& organization, const std::string& description, const std::string& fileServer, const std::string& brokerList, const std::string& inops, const std::string& flops)
{
	return m_brokerAgent.checkIn(workerVersion, nCore, internalIp, hostName, os, organization, description, fileServer, brokerList, inops, flops);
}

inline int BrokerAgentExtension::recheckIn()
{
	return m_brokerAgent.recheckIn();
}

inline int BrokerAgentExtension::checkOut()
{
	return m_brokerAgent.checkOut();
}

inline int BrokerAgentExtension::sendAlive(
	int nCoreNum,
	int nCoreUsed,
	unsigned cpuSpeed, // in MHz
	unsigned cpuUsage, // in %
	unsigned ramSize, // in MB
	unsigned ramUsage, // in %
	double inops, // in operations/second
	double flops // in operations/second
)
{
	return m_brokerAgent.sendAlive(nCoreNum, nCoreUsed, cpuSpeed, cpuUsage, ramSize, ramUsage, inops, flops);
}

inline int BrokerAgentExtension::sendJobDoing(int iUId, int iJId)
{
	return m_brokerAgent.sendJobDoing(iUId, iJId);
}

inline int BrokerAgentExtension::sendJobMessage(int iUId, int iJId, const std::string& applicationName,
                           const std::string& applicationVersion, const std::string& jobMessage)
{
	return m_brokerAgent.sendJobMessage(iUId, iJId, applicationName, applicationVersion, jobMessage);
}

inline int BrokerAgentExtension::sendJobFail(int iUId, int iJId, const std::string& errorCode, const std::string& message)
{
	return m_brokerAgent.sendJobFail(iUId, iJId, errorCode, message);
}

inline int BrokerAgentExtension::sendJobDone(int iUId, int iJId, const std::string& uTime, const std::string& kTime)
{
	return m_brokerAgent.sendJobDone(iUId, iJId, uTime, kTime);
}

inline int BrokerAgentExtension::sendJobAbortAck(int iUId, int iJId, const std::string& errorCode, const std::string& message)
{
	return m_brokerAgent.sendJobAbortAck(iUId, iJId, errorCode, message);
}

inline int BrokerAgentExtension::sendSleep()
{
	return m_brokerAgent.sendSleep();
}

inline int BrokerAgentExtension::sendWakeUp()
{
	return m_brokerAgent.sendWakeUp();
}

inline int BrokerAgentExtension::sendUpdateWorkerAck(const std::string& errorCode, const std::string& message)
{
	return m_brokerAgent.sendUpdateWorkerAck(errorCode, message);
}

inline int BrokerAgentExtension::sendJSetCore(int iUId, int iJId, int iWId, int iCore, int iSetCore) 
{
	return m_brokerAgent.sendJSetCore(iUId, iJId, iWId, iCore, iSetCore);
}

inline int BrokerAgentExtension::sendJSetCoreAck(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& sErrorCode, const std::string& sMessage)
{
	return m_brokerAgent.sendJSetCoreAck(iUId, iJId, iWId, iCore, iSetCore, sErrorCode, sMessage);
}

	}
}

#endif
