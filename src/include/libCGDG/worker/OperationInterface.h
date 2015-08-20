#ifndef WORKER_OPERATIONINTERFACE_H
#define WORKER_OPERATIONINTERFACE_H

namespace cgdg
{
	namespace worker
	{

class OperationInterface
{
public:
	virtual int checkIn(const std::string& workerVersion, int nCore, const std::string& internalIp, const std::string& hostName,
	                    const std::string& os, const std::string& organization, const std::string& description, const std::string& fileServer, const std::string& brokerList, const std::string& inops, const std::string& flops) = 0;
	virtual int recheckIn() = 0;
	virtual int checkOut() = 0;
	virtual int sendAlive(
		int nCoreNum,
		int nCoreUsed,
		unsigned cpuSpeed, // in MHz
		unsigned cpuUsage, // in %
		unsigned ramSize, // in MB
		unsigned ramUsage, // in %
		double inops, // in operations/second
		double flops // in operations/second
	) = 0;
	virtual int sendJobDoing(int iUId, int iJId) = 0;
	virtual int sendJobMessage(int iUId, int iJId, const std::string& applicationName,
	                           const std::string& applicationVersion, const std::string& jobMessage) = 0;
	virtual int sendJobFail(int iUId, int iJId, const std::string& errorCode, const std::string& message) = 0;
	virtual int sendJobDone(int iUId, int iJId, const std::string& uTime, const std::string& kTime) = 0;
	virtual int sendJobAbortAck(int iUId, int iJId, const std::string& errorCode, const std::string& message) = 0;
	virtual int sendSleep() = 0;
	virtual int sendWakeUp() = 0;
	virtual int sendUpdateWorkerAck(const std::string& errorCode, const std::string& message) = 0;
	virtual int sendJSetCore(int iUId, int iJId, int iWId, int iCore, int iSetCore) = 0;
	virtual int sendJSetCoreAck(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& sErrorCode, const std::string& sMessage) = 0;
};

	}
}

#endif
