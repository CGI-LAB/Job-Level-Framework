#ifndef CONNECTHELPER_H
#define CONNECTHELPER_H

#include "common/ConnectConfig.h"
#include "common/SocketFactoryInterface.h"
#include "common/NonblockingIOInterface.h"
#include "common/HandlerInterface.h"
#include "common/BaseBrokerAgent.h"
#include "common/SocketInterface.h"
#include <string>
#include <algorithm>

namespace cgdg
{
	namespace common
	{

class ConnectHelper
{
public:
	ConnectHelper(SocketFactoryInterface& aliasSocketFactory);
	~ConnectHelper();
	void setConnectConfig(const ConnectConfig& connectConfig);

	BaseBrokerAgent::ErrorCode processReadEvent();
	BaseBrokerAgent::ErrorCode processWriteEvent();
	BaseBrokerAgent::ErrorCode processConnectEvent(SocketInterface::ConnectionResult result); //socket level
	BaseBrokerAgent::ErrorCode processCloseEvent(); //socket level

	void doReconnection();
	void doDemandConnection(const std::string& host, unsigned short port);
	void doFirstTimeConnection();
	void close();
	void setShouldClose(bool bShouldClose);
	bool shouldClose() const;
	bool isSameBroker() const;
	bool isConnected() const;
	void setHandler(HandlerInterface* pHandler);
	void setBrokerAgent(BaseBrokerAgent* pBrokerAgent);

	SocketInterface* getSocket();

private:
	void doConnection(const std::string& host, unsigned short port);

	SocketFactoryInterface& m_aliasSocketFactory;
	HandlerInterface* m_pHandler;
	BaseBrokerAgent* m_pBrokerAgent;
	ConnectConfig m_connectConfig;
	SocketInterface* m_pSocket;

	std::string m_currentHost;
	unsigned short m_currentPort;

	bool m_bShouldClose;
	bool m_bIsSameBroker;
	int m_iSelectedTarget;
	bool m_bIsConnected;
};

inline ConnectHelper::ConnectHelper(SocketFactoryInterface& aliasSocketFactory) :
m_aliasSocketFactory(aliasSocketFactory),
m_pHandler(NULL),
m_pBrokerAgent(NULL),
m_pSocket(NULL),
m_bShouldClose(false),
m_bIsSameBroker(false),
m_iSelectedTarget(0),
m_bIsConnected(false)
{
}

inline ConnectHelper::~ConnectHelper()
{
	close();
	SocketInterface* pSocket;
	pSocket = dynamic_cast<SocketInterface*>(m_pBrokerAgent->changeIOInterface(NULL));
	m_aliasSocketFactory.destroySocket(pSocket);
}

inline void ConnectHelper::setConnectConfig(const ConnectConfig& connectConfig)
{
	m_connectConfig = connectConfig;
	std::random_shuffle(m_connectConfig.getConnectTargets().begin(), m_connectConfig.getConnectTargets().end());
}

inline void ConnectHelper::setShouldClose(bool bShouldClose)
{
	m_bShouldClose = bShouldClose;
}

inline bool ConnectHelper::shouldClose() const
{
	return m_bShouldClose;
}

inline bool ConnectHelper::isSameBroker() const
{
	return m_bIsSameBroker;
}

inline bool ConnectHelper::isConnected() const
{
	return m_bIsConnected;
}

inline void ConnectHelper::setHandler(HandlerInterface* pHandler)
{
	m_pHandler = pHandler;
}

inline void ConnectHelper::setBrokerAgent(BaseBrokerAgent* pBrokerAgent)
{
	m_pBrokerAgent = pBrokerAgent;
}

inline SocketInterface* ConnectHelper::getSocket()
{
	return m_pSocket;
}

	}
}

#endif
