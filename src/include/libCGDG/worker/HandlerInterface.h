#ifndef WORKER_HANDLERINTERFACE_H
#define WORKER_HANDLERINTERFACE_H

#include "common/HandlerInterface.h"
#include <string>

namespace cgdg
{
	namespace worker
	{

class HandlerInterface : public common::HandlerInterface
{
public:
	virtual void handleInitWorker(const std::string& brokerVersion, const std::string& workerVersion) = 0;

	virtual void handleJAssign(int iUId, int iJId, const std::string& applicationName, const std::string& applicationVersion, int nCore, const std::string& argument) = 0;
	virtual void handleJAbort(int iUId, int iJId) = 0;
	virtual void handleJIn(int iUId, int iJId, const std::string& jobInput) = 0;

	virtual void handleInitDaemon(const std::string& daemonRatio) = 0;
	virtual void handleUpdateWorker(const std::string& workerVersion, const std::string brokerHost, unsigned short brokerPort,
	                                const std::string& organization, int nCore, const std::string& fileServer, const std::string& brokerList) = 0;

	virtual void handleJSetCore(int iUId, int iJId, int iWId, int iCore, int iSetCore) = 0;
	virtual void handleJSetCoreAck(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& serrorCode, const std::string& sMessage) = 0;
	virtual void handleUnknown(const std::string& commandXmlString) = 0;
};

	}
}

#endif
