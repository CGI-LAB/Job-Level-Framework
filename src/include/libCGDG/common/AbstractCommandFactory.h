#ifndef ABSTRACTCOMMANDFACTORY_H
#define ABSTRACTCOMMANDFACTORY_H

#include <string>
#include "common/Command.h"
#include "common/CommandData.h"
#include "common/NewConnectData.h"
#include "common/ExitData.h"

namespace cgdg
{
	namespace common
	{

class AbstractCommandFactory
{
public:
	AbstractCommandFactory();
	enum {
		COMMANDTYPE_NEW_CONNECT,
		COMMANDTYPE_EXIT,
		COMMANDTYPE_INIT_CONNECT,
		COMMANDTYPE_HEART_BEAT,
		COMMANDTYPE_UNKNOWN
	};
	Command load(const std::string& xmlString);
	virtual CommandData* makeCommandData(Command::CommandType commandType) = 0;
	std::string translateToXml(const Command& command);

	virtual std::string translateToString(Command::CommandType commandType) = 0;
	virtual Command::CommandType translateToCommandType(const std::string& commandString) = 0;

	Command makeNewConnectCommand();
	Command makeExitCommand();

	void resetCommandId();

private:
	unsigned m_iLastSentCommandId;

	Command makeCommand(Command::CommandType commandType, CommandData* pData, unsigned iCommandId);
protected:
	Command makeCommand(Command::CommandType commandType, CommandData* pData);
};

inline AbstractCommandFactory::AbstractCommandFactory()
{
	resetCommandId();
}

inline Command AbstractCommandFactory::makeCommand(Command::CommandType commandType, CommandData *pData, unsigned iCommandId)
{
	return Command(commandType, pData, iCommandId);
}

inline Command AbstractCommandFactory::makeCommand(Command::CommandType commandType, CommandData *pData)
{
	return Command(commandType, pData, ++m_iLastSentCommandId);
}

inline Command AbstractCommandFactory::makeNewConnectCommand()
{
	return makeCommand(COMMANDTYPE_NEW_CONNECT, new NewConnectData());
}

inline Command AbstractCommandFactory::makeExitCommand()
{
	return makeCommand(COMMANDTYPE_EXIT, new ExitData());
}

inline void AbstractCommandFactory::resetCommandId()
{
	m_iLastSentCommandId = 0;
}

	}
}

#endif
