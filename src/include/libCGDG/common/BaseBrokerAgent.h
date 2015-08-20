#ifndef BASEBROKERAGENT_H
#define BASEBROKERAGENT_H

#include "common/AbstractCommandFactory.h"
#include "common/Logger.h"
#include "common/NonblockingIOInterface.h"
#include "common/ConnectConfig.h"
#include "common/HandlerInterface.h"
#include <queue>

namespace cgdg
{
	namespace common
	{

class BaseBrokerAgent
{
public:
	enum {
		ERRORCODE_SUCCESS,
		ERRORCODE_WRITEERROR,
		ERRORCODE_READERROR,
		ERRORCODE_ENDOFFILE,
		ERRORCODE_OTHER,
		ERRORCODE_NOIOINTERFACE,
		ERRORCODE_BLOCK
	};
	typedef int ErrorCode;

	BaseBrokerAgent(AbstractCommandFactory& aliasCommandFactory);

	bool hasUnsentCommand() const;
	bool hasUnackedCommand() const;
	NonblockingIOInterface* changeIOInterface(NonblockingIOInterface* pIOInterface);
	void clearUnsentCommands();
	void clearUnackedCommands();
	ErrorCode sendUnackedCommands();

	ErrorCode requestConnectionDestination();

	void setHandler(HandlerInterface* pHandler);
	HandlerInterface* getHandler();

	int exit();

	//OS dependent
	ErrorCode processReadEvent();
	ErrorCode processWriteEvent();

	void resetCommandIdRecord();

protected:
	virtual void preprocess(const Command& command);
	virtual ErrorCode dispatch(const Command& command);
	ErrorCode receiveCommand(const Command& command);
	ErrorCode postCommand(const Command& command);

	AbstractCommandFactory& getCommandFactory();

private:
	BaseBrokerAgent(const BaseBrokerAgent&);
	BaseBrokerAgent& operator=(const BaseBrokerAgent&);

	static const unsigned BUFFER_SIZE = 65536;

	std::string m_bufferString;

	NonblockingIOInterface* m_pIOInterface;
	AbstractCommandFactory& m_aliasCommandFactory;
	HandlerInterface* m_pHandler;
	
	std::queue<Command> m_unsentCommands;
	std::queue<Command> m_unackedCommands;
	unsigned m_iLastReceivedCommandId;
	unsigned m_iLastArrivedCommandId;
};

inline BaseBrokerAgent::BaseBrokerAgent(AbstractCommandFactory& aliasCommandFactory)
: m_pIOInterface(NULL), m_aliasCommandFactory(aliasCommandFactory), m_pHandler(NULL), m_iLastReceivedCommandId(0), m_iLastArrivedCommandId(0)
{
	resetCommandIdRecord();
}

inline BaseBrokerAgent::ErrorCode BaseBrokerAgent::requestConnectionDestination()
{
	resetCommandIdRecord();
	Command command = getCommandFactory().makeNewConnectCommand();
	return dispatch(command);
}

inline void BaseBrokerAgent::setHandler(HandlerInterface* pHandler)
{
	m_pHandler = pHandler;
}

inline int BaseBrokerAgent::exit()
{
	Command command = getCommandFactory().makeExitCommand();
	return dispatch(command);
}

inline AbstractCommandFactory& BaseBrokerAgent::getCommandFactory()
{
	return m_aliasCommandFactory;
}

inline bool BaseBrokerAgent::hasUnsentCommand() const
{
	return !m_unsentCommands.empty();
}

inline bool BaseBrokerAgent::hasUnackedCommand() const
{
	return !m_unackedCommands.empty();
}

inline NonblockingIOInterface* BaseBrokerAgent::changeIOInterface(NonblockingIOInterface* pIOInterface)
{
	NonblockingIOInterface* pOldIOInterface = m_pIOInterface;
	m_pIOInterface = pIOInterface;
	return pOldIOInterface;
}

inline void BaseBrokerAgent::clearUnsentCommands()
{
	m_unsentCommands = std::queue<Command>();
}

inline void BaseBrokerAgent::clearUnackedCommands()
{
	while (hasUnackedCommand()) {
		assert(m_unackedCommands.front().getCommandId() <= m_iLastArrivedCommandId || m_unackedCommands.front().getCommandId() == m_iLastArrivedCommandId + 1);
		m_iLastArrivedCommandId = m_unackedCommands.front().getCommandId() > m_iLastArrivedCommandId? m_unackedCommands.front().getCommandId(): m_iLastArrivedCommandId;
		m_unackedCommands.pop();
	}
}

inline void BaseBrokerAgent::resetCommandIdRecord()
{
	getCommandFactory().resetCommandId();
	m_iLastReceivedCommandId = 0;
	m_iLastArrivedCommandId = 0;
	m_unackedCommands = std::queue<Command>();
}

	}
}

#endif
