#ifndef CLIENT_JOBOPERATIONINTERFACEEXTENSION_H
#define CLIENT_JOBOPERATIONINTERFACEEXTENSION_H

#include <string>
#include "client/CompositeType.h"

namespace cgdg
{
	namespace client
	{

class JobOperationInterfaceExtension
{
public:
	virtual int submitJob(const std::string& applicationName, const std::string& applicationVersion, int m_iPrioirty, const std::string& argument,
	                      int nCores = 1, bool bIsAbortable = false, const std::string& averageTime = "", const std::string& maxTime = "") = 0;
	virtual int abortJob(int iJId) = 0;
	virtual int sendJobinput(int iJId, const std::string& jobInput) = 0;
	virtual int selectWorker(const std::vector<int>& targets, int prioirty, int nMaxCore) = 0;
	virtual int selectWorker(const std::vector<Filter>& filters, int prioirty) = 0;
};

	}
}

#endif
