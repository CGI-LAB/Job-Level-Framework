#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>
#include "common/CommandData.h"

namespace cgdg
{
	namespace common
	{

class Command
{
	friend class AbstractCommandFactory;
public:
	typedef int CommandType;

	CommandType getCommandType() const;
	template<typename CommandDataType>
	const CommandDataType* getCommandData() const;
	template<typename CommandDataType>
	CommandDataType* getCommandData();
	unsigned getCommandId() const;

	Command(const Command& command);
	~Command();

private:
	Command(CommandType commandType, CommandData* pData, unsigned iCommandId);

	CommandType m_commandType;
	CommandData* m_pData;
	unsigned m_iCommandId;
};

inline Command::Command(CommandType commandType, CommandData *pData, unsigned iCommandId)
: m_commandType(commandType), m_pData(pData), m_iCommandId(iCommandId)
{
	assert(pData != NULL);
}

inline Command::Command(const Command& command)
: m_commandType(command.m_commandType), m_pData(command.m_pData), m_iCommandId(command.m_iCommandId)
{
	const_cast<Command&>(command).m_commandType = -1;
	const_cast<Command&>(command).m_pData = NULL;
	const_cast<Command&>(command).m_iCommandId = 0;
}

inline Command::~Command()
{
	if (m_pData != NULL) delete m_pData;
}

inline Command::CommandType Command::getCommandType() const
{
	return m_commandType;
}

template<typename CommandDataType>
CommandDataType* Command::getCommandData()
{
	return dynamic_cast<CommandDataType*>(m_pData);
}

template<typename CommandDataType>
const CommandDataType* Command::getCommandData() const
{
	return dynamic_cast<const CommandDataType*>(m_pData);
}

inline unsigned Command::getCommandId() const
{
	return m_iCommandId;
}

	}
}

#endif
