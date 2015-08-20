#ifndef CLIENT_OPERATIONINTERFACE_H
#define CLIENT_OPERATIONINTERFACE_H

#include <string>
#include <vector>

namespace cgdg
{
	namespace client
	{

class OperationInterface
{
public:
	virtual int login(const std::string& userName, const std::string& password, const std::string& description) = 0;
	virtual int recheckIn() = 0;
	virtual int logout() = 0;
	virtual int updateWorkerInfo(const std::vector<int>& iWIds) = 0;
	virtual int updateWorkerInfo(const std::string& organization) = 0;
	virtual int updateWorkerInfo() = 0;
	virtual int selectWorker(const std::vector<int>& targets, int iPrioirty, int nMaxCore) = 0;
	virtual int selectWorker(const std::vector<Filter>& filters, int iPrioirty) = 0;
	virtual int submitJob(int iJId, const std::string& applicationName, const std::string& applicationVersion, int iPrioirty,
	                      int nCores, bool bIsAbortable, const std::string& averageTime, const std::string& maxTime, const std::string& argument) = 0;
	virtual int abortJob(int iJId) = 0;
	virtual int sendJobinput(int iJId, const std::string& jobInput) = 0;
};

	}
}

#endif
