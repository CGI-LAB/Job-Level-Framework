#ifndef ENDTEMPLATE_H
#define ENDTEMPLATE_H

#include "common/ConnectHelper.h"
#include "common/BaseBrokerAgent.h"
#include "common/Logger.h"

namespace cgdg
{
	namespace common
	{

template<typename HandlerInterfaceType, typename BrokerAgentType>
class EndTemplate
{
public:
	EndTemplate(SocketFactoryInterface& aliasSocketFactory);

	void setHandler(HandlerInterfaceType* pHandler);
	void setConnectConfig(const ConnectConfig& connectConfig);

	bool isConnected() const;
	bool hasUnsentCommand() const;

	BaseBrokerAgent::ErrorCode processReadEvent();
	BaseBrokerAgent::ErrorCode processWriteEvent();
	BaseBrokerAgent::ErrorCode processConnectEvent(SocketInterface::ConnectionResult result);
	BaseBrokerAgent::ErrorCode processCloseEvent();
	BaseBrokerAgent::ErrorCode processNoResponseEvent();
	
	void doReconnection();
	void doDemandConnection(const std::string& host, unsigned short port);
	void doFirstTimeConnection();

protected:
	BrokerAgentType m_brokerAgent;
	ConnectHelper m_connectHelper;
};

template<typename HandlerInterfaceType, typename BrokerAgentType>
EndTemplate<HandlerInterfaceType, BrokerAgentType>::EndTemplate(SocketFactoryInterface& aliasSocketFactory)
: m_connectHelper(aliasSocketFactory)
{
	m_connectHelper.setBrokerAgent(&m_brokerAgent);
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
void EndTemplate<HandlerInterfaceType, BrokerAgentType>::setConnectConfig(const ConnectConfig& connectConfig)
{
	m_connectHelper.setConnectConfig(connectConfig);
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
void EndTemplate<HandlerInterfaceType, BrokerAgentType>::setHandler(HandlerInterfaceType* pHandler)
{
	m_brokerAgent.setHandler(pHandler);
	m_connectHelper.setHandler(pHandler);
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
bool EndTemplate<HandlerInterfaceType, BrokerAgentType>::isConnected() const
{
	return m_connectHelper.isConnected();
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
bool EndTemplate<HandlerInterfaceType, BrokerAgentType>::hasUnsentCommand() const
{
	return m_brokerAgent.hasUnsentCommand();
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
BaseBrokerAgent::ErrorCode EndTemplate<HandlerInterfaceType, BrokerAgentType>::processReadEvent()
{
	Logger::getInstance().log(3, "event", "read event");
	return m_connectHelper.processReadEvent();
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
BaseBrokerAgent::ErrorCode EndTemplate<HandlerInterfaceType, BrokerAgentType>::processWriteEvent()
{
	Logger::getInstance().log(3, "event", "write event");
	return m_connectHelper.processWriteEvent();
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
BaseBrokerAgent::ErrorCode EndTemplate<HandlerInterfaceType, BrokerAgentType>::processConnectEvent(SocketInterface::ConnectionResult result)
{
	Logger::getInstance().log(3, "event", std::string("connect ") + (result == SocketInterface::CONNECTIONRESULT_SUCESS? "sucess": "fail") + " event");
	return m_connectHelper.processConnectEvent(result);
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
BaseBrokerAgent::ErrorCode EndTemplate<HandlerInterfaceType, BrokerAgentType>::processCloseEvent()
{
	Logger::getInstance().log(3, "event", "close event");
	return m_connectHelper.processCloseEvent();
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
BaseBrokerAgent::ErrorCode EndTemplate<HandlerInterfaceType, BrokerAgentType>::processNoResponseEvent()
{
	Logger::getInstance().log(3, "event", "no response event");
	return processCloseEvent();
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
void EndTemplate<HandlerInterfaceType, BrokerAgentType>::doReconnection()
{
	m_connectHelper.doReconnection();
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
void EndTemplate<HandlerInterfaceType, BrokerAgentType>::doDemandConnection(const std::string& host, unsigned short port)
{
	m_connectHelper.doDemandConnection(host, port);
}

template<typename HandlerInterfaceType, typename BrokerAgentType>
void EndTemplate<HandlerInterfaceType, BrokerAgentType>::doFirstTimeConnection()
{
	m_connectHelper.doFirstTimeConnection();
}

	}
}

#endif
