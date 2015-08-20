#ifndef SOCKETINTERFACE_H
#define SOCKETINTERFACE_H

#include <string>
#include "common/NonblockingIOInterface.h"

namespace cgdg
{
	namespace common
	{

class SocketInterface : public NonblockingIOInterface
{
public:
	enum ConnectionResult
	{
		CONNECTIONRESULT_SUCESS,
		CONNECTIONRESULT_FAIL
	};
	virtual int connect(const std::string& host, unsigned short port) = 0;
	virtual void close() = 0;
};

	}
}

#endif
