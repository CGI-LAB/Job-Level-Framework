#ifndef COMMON_HANDLERINTERFACE_H
#define COMMON_HANDLERINTERFACE_H

namespace cgdg
{
	namespace common
	{

#include <string>

class HandlerInterface
{
public:
	//common
	virtual void handleInitConnect(const std::string& host, unsigned short port) = 0;
	virtual void handleHeartBeat() = 0;
	virtual void handleFirstTimeConnection() = 0;
	virtual void handleReconnection() = 0;
	virtual void handleConnectionFail() = 0;
	virtual void handleConnectionDown() = 0;
	virtual void handleSameSessionId() = 0;
	virtual void handleSessionIdChanged() = 0;
};

	}
}

#endif
