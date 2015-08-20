#ifndef CLIENT_HANDLERINTERFACE_H
#define CLIENT_HANDLERINTERFACE_H

#include <string>
#include "client/CompositeType.h"
#include "common/HandlerInterface.h"
#include "client/JobHandlerInterface.h"

namespace cgdg
{
	namespace client
	{

class HandlerInterface : public common::HandlerInterface, public client::JobHandlerInterface
{
public:
	//client
	virtual void handleAuthResult(const std::string& errorCode, const std::string& message) = 0;
	virtual void handleSelectionResult(const std::string& errorCode, const std::string& message, const std::vector<int>& workerList) = 0;
	virtual void handleWorkerLost(int iWId) = 0;
	virtual void handleWorkerInfo(const WorkerStatus& workerStatus) = 0;
	virtual void handleUnknown(const std::string& commandXmlString) = 0;
};

	}
}

#endif
