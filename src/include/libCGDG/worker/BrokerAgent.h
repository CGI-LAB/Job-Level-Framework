#ifndef WORKER_BROKERAGENT_H
#define WORKER_BROKERAGENT_H

#include "common/BaseBrokerAgent.h"
#include "worker/HandlerInterface.h"
#include "worker/OperationInterface.h"
#include "worker/WorkerCommandFactory.h"

namespace cgdg
{
	namespace worker
	{

class BrokerAgent : public common::BaseBrokerAgent, public OperationInterface
{
public:
	enum {
		ERRORCODE_NOTCHECKEDIN = ERRORCODE_BLOCK + 1
	};

	BrokerAgent();

	void setHandler(HandlerInterface* pHandler);
	HandlerInterface* getHandler();

	bool isCheckedIn() const;

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


protected:
	virtual void preprocess(const common::Command& command);
	virtual ErrorCode dispatch(const common::Command& command);
	WorkerCommandFactory& getCommandFactory();

private:	
	static const std::string W_VERSION;
	static const std::string B_VERSION;

	BrokerAgent(const BrokerAgent&);
	BrokerAgent& operator=(const BrokerAgent&);

	int m_iWId;

	std::string m_workerVersion;
	int m_nCore;
	std::string m_internalIp;
	std::string m_hostName;
	std::string m_os;
	std::string m_organization;
	std::string m_description;
	std::string m_fileServer;
	std::string m_brokerList;
	std::string m_inops;
	std::string m_flops;

	WorkerCommandFactory m_commandFactory;

	HandlerInterface* m_pHandler;
};

inline void BrokerAgent::setHandler(HandlerInterface* pHandler)
{
	assert(pHandler != NULL);
	BaseBrokerAgent::setHandler(pHandler);
	m_pHandler = pHandler;
}

inline WorkerCommandFactory& BrokerAgent::getCommandFactory()
{
	return m_commandFactory;
}

inline bool BrokerAgent::isCheckedIn() const
{
	return m_iWId != 0;
}

	}
}

#endif
