#ifndef CLIENT_OPERATIONINTERFACEEXTENSION_H
#define CLIENT_OPERATIONINTERFACEEXTENSION_H

#include <string>
#include <vector>
#include "client/JobOperationInterfaceExtension.h"

namespace cgdg
{
	namespace client
	{

class OperationInterfaceExtension : public cgdg::client::JobOperationInterfaceExtension
{
public:
	virtual int login(const std::string& userName, const std::string& password, const std::string& description) = 0;
	virtual int recheckIn() = 0;
	virtual int logout() = 0;
	virtual int updateWorkerInfo(const std::vector<int>& iWIds) = 0;
	virtual int updateWorkerInfo(const std::string& organization) = 0;
	virtual int updateWorkerInfo() = 0;
};

	}
}

#endif
