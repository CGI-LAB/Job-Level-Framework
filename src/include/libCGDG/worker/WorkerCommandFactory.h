#ifndef WORKERCOMMANDFACTORY_H
#define WORKERCOMMANDFACTORY_H

#include "common/AbstractCommandFactory.h"

#include "common/Command.h"
#include "common/CommandData.h"
#include "worker/NewWorkerData.h"
#include "common/JDoingData.h"
#include "common/JFailData.h"
#include "worker/JDoneData.h"
#include "common/JMsgData.h"
#include "common/JAbortAckData.h"
#include "worker/WAliveData.h"
#include "worker/WSleepData.h"
#include "worker/WWakeUpData.h"
#include "worker/UpdateWorkerAckData.h"
#include "worker/JSetCoreData.h"
#include "worker/JSetCoreAckData.h"

namespace cgdg
{
	namespace worker
	{

class WorkerCommandFactory : public common::AbstractCommandFactory
{
public:
	enum {
		//received commands
		COMMANDTYPE_JASSIGN = COMMANDTYPE_UNKNOWN + 1,
		COMMANDTYPE_JABORT,
		COMMANDTYPE_INIT_WORKER,
		COMMANDTYPE_INIT_DAEMON,
		COMMANDTYPE_UPDATE_WORKER,
		COMMANDTYPE_JIN,
		COMMANDTYPE_JSETCORE_RCV,			// JSetCore has send and receive parts, mikekao
		COMMANDTYPE_JSETCORE_ACK_RCV,		// JSetCoreAck has send and receive parts, mikekao
		//sent commands
		COMMANDTYPE_NEW_WORKER,
		COMMANDTYPE_JDOING,
		COMMANDTYPE_JFAIL,
		COMMANDTYPE_JDONE,
		COMMANDTYPE_JMSG,
		COMMANDTYPE_JABORT_ACK,
		COMMANDTYPE_WALIVE,
		COMMANDTYPE_WSLEEP,
		COMMANDTYPE_WWAKEUP,
		COMMANDTYPE_UPDATE_WORKER_ACK,
		COMMANDTYPE_JSETCORE_SEND,			// JSetCore has send and receive parts, mikekao
		COMMANDTYPE_JSETCORE_ACK_SEND		// JSetCoreAck has send and receive parts, mikekao
	};

	// receive command method
	virtual common::CommandData* makeCommandData(common::Command::CommandType commandType);

	// translator
	virtual std::string translateToString(common::Command::CommandType commandType);
	virtual common::Command::CommandType translateToCommandType(const std::string& commandString);

	// send command method
	common::Command makeNewWorkerCommand(int iWId, const std::string& workerVersion, int nCore, const std::string& internalIp, const std::string& hostName,
	                                     const std::string& os, const std::string& organization, const std::string& description, const std::string& fileServer, const std::string& brokerList, const std::string& inops, const std::string& flops);
	common::Command makeNewWorkerCommand(const std::string& workerVersion, int nCore, const std::string& internalIp, const std::string& hostName,
	                                     const std::string& os, const std::string& organization, const std::string& description, const std::string& fileServer, const std::string& brokerList, const std::string& inops, const std::string& flops);
	common::Command makeJDoingCommand(int iUId, int iJId, int iWId);
	common::Command makeJFailCommand(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string message);
	common::Command makeJDoneCommand(int iUId, int iJId, int iWId, const std::string& uTime, const std::string& kTime);
	common::Command makeJMsgCommand(int iUId, int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage);
	common::Command makeJAbortAckCommand(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string& message);
	common::Command makeWAliveCommand(
		int iWId,
		int nCoreNum,
		int nCoreUsed,
		unsigned cpuSpeed, // in MHz
		unsigned cpuUsage, // in %
		unsigned ramSize, // in MB
		unsigned ramUsage, // in %
		double inops, // in operations/second
		double flops // in operations/second
	);
	common::Command makeWSleepCommand(int iWId);
	common::Command makeWWakeUpCommand(int iWId);
	common::Command makeUpdateWorkerAckCommand(const std::string& errorCode, const std::string& message);
	common::Command makeJSetCoreCommand(int iUId, int iJId, int iWId, int iCore, int iSetCore);
	common::Command makeJSetCoreAckCommand(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& sErrorCode, const std::string& sMessage);
};

inline common::Command WorkerCommandFactory::makeNewWorkerCommand(
	int iWId,
	const std::string& workerVersion,
	int nCore,
	const std::string& internalIp,
	const std::string& hostName,
	const std::string& os,
	const std::string& organization,
	const std::string& description,
	const std::string& fileServer,
	const std::string& brokerList,
	const std::string& inops,
	const std::string& flops
)
{
	return makeCommand(COMMANDTYPE_NEW_WORKER, new NewWorkerData(iWId, workerVersion, nCore, internalIp, hostName, os, organization, description, fileServer, brokerList, inops, flops));
}

inline common::Command WorkerCommandFactory::makeNewWorkerCommand(
	const std::string& workerVersion,
	int nCore,
	const std::string& internalIp,
	const std::string& hostName,
	const std::string& os,
	const std::string& organization,
	const std::string& description,
	const std::string& fileServer,
	const std::string& brokerList,
	const std::string& inops,
	const std::string& flops
)
{
	return makeCommand(COMMANDTYPE_NEW_WORKER, new NewWorkerData(0, workerVersion, nCore, internalIp, hostName, os, organization, description, fileServer, brokerList, inops, flops));
}

inline common::Command WorkerCommandFactory::makeJDoingCommand(int iUId, int iJId, int iWId)
{
	return makeCommand(COMMANDTYPE_JDOING, new common::JDoingData(iUId, iJId, iWId));
}

inline common::Command WorkerCommandFactory::makeJFailCommand(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string message)
{
	return makeCommand(COMMANDTYPE_JFAIL, new common::JFailData(iUId, iJId, iWId, errorCode, message));
}

inline common::Command WorkerCommandFactory::makeJDoneCommand(int iUId, int iJId, int iWId, const std::string& uTime, const std::string& kTime)
{
	return makeCommand(COMMANDTYPE_JDONE, new worker::JDoneData(iUId, iJId, iWId, uTime, kTime));
}

inline common::Command WorkerCommandFactory::makeJMsgCommand(int iUId, int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage)
{
	return makeCommand(COMMANDTYPE_JMSG, new common::JMsgData(iUId, iJId, iWId, applicationName, applicationVersion, jobMessage));
}

inline common::Command WorkerCommandFactory::makeJAbortAckCommand(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string& message)
{
	return makeCommand(COMMANDTYPE_JABORT_ACK, new common::JAbortAckData(iUId, iJId, iWId, errorCode, message));
}

inline common::Command WorkerCommandFactory::makeWAliveCommand(
	int iWId,
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
	return makeCommand(COMMANDTYPE_WALIVE,
	                   new WAliveData(iWId,
	                                  nCoreNum,
	                                  nCoreUsed,
	                                  cpuSpeed,
	                                  cpuUsage,
	                                  ramSize,
	                                  ramUsage,
	                                  inops,
	                                  flops
	                                  )
	                   );
}


inline common::Command WorkerCommandFactory::makeWSleepCommand(int iWId)
{
	return makeCommand(COMMANDTYPE_WSLEEP, new WSleepData(iWId));
}

inline common::Command WorkerCommandFactory::makeWWakeUpCommand(int iWId)
{
	return makeCommand(COMMANDTYPE_WWAKEUP, new WWakeUpData(iWId));
}

inline common::Command WorkerCommandFactory::makeUpdateWorkerAckCommand(const std::string& errorCode, const std::string& message)
{
	return makeCommand(COMMANDTYPE_UPDATE_WORKER_ACK, new UpdateWorkerAckData(errorCode, message));
}

inline common::Command WorkerCommandFactory::makeJSetCoreCommand(int iUId, int iJId, int iWId, int iCore, int iSetCore)
{
	return makeCommand(COMMANDTYPE_JSETCORE_SEND, new JSetCoreData(iUId, iJId, iWId, iCore, iSetCore));
}

inline common::Command WorkerCommandFactory::makeJSetCoreAckCommand(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& sErrorCode, const std::string& sMessage)
{
	return makeCommand(COMMANDTYPE_JSETCORE_ACK_SEND, new JSetCoreAckData(iUId, iJId, iWId, iCore, iSetCore, sErrorCode, sMessage));
}

	}
}

#endif
