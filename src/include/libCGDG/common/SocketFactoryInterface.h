#ifndef SOCKETFACTORYINTERFACE_H
#define SOCKETFACTORYINTERFACE_H

#include "common/SocketInterface.h"

namespace cgdg
{
	namespace common
	{

class SocketFactoryInterface
{
public:
	virtual SocketInterface* makeSocket() = 0;
	virtual void destroySocket(SocketInterface* pSocket) = 0;
};

	}
}

#endif
