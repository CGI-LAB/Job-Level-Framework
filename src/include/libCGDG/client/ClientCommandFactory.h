#ifndef CLIENTCOMMANDFACTORY_H
#define CLIENTCOMMANDFACTORY_H

#include "common/AbstractCommandFactory.h"

#include "common/Command.h"
#include "common/CommandData.h"
#include "client/NewUserData.h"
#include "client/AskInfoData.h"
#include "client/JSubmitData.h"
#include "common/JAbortData.h"
#include "client/WSelectData.h"
#include "common/JInData.h"

namespace cgdg
{
	namespace client
	{

class ClientCommandFactory : public common::AbstractCommandFactory
{
public:
	enum {
		//sent commands
		COMMANDTYPE_NEW_USER = COMMANDTYPE_UNKNOWN + 1,
		COMMANDTYPE_ASK_INFO,
		COMMANDTYPE_WSELECT,
		COMMANDTYPE_JSUBMIT,
		COMMANDTYPE_JABORT,
		COMMANDTYPE_JIN,
		//received commands
		COMMANDTYPE_INIT_USER,
		COMMANDTYPE_REJECT_USER,
		COMMANDTYPE_WLOST,
		COMMANDTYPE_WINFO,
		COMMANDTYPE_WSELECT_ACK,
		COMMANDTYPE_JNEXT,
		COMMANDTYPE_JSUBMIT_ACK,
		COMMANDTYPE_JABORT_ACK,
		COMMANDTYPE_JASSIGNDONE,
		COMMANDTYPE_JDOING,
		COMMANDTYPE_JMSG,
		COMMANDTYPE_JFAIL,
		COMMANDTYPE_JDROP,
		COMMANDTYPE_JDONE
	};

	virtual common::CommandData* makeCommandData(common::Command::CommandType commandType);

	virtual std::string translateToString(common::Command::CommandType commandType);
	virtual common::Command::CommandType translateToCommandType(const std::string& commandString);

	common::Command makeNewUserCommand(const std::string& cVersion, const std::string& userName, const std::string& password, const std::string& description);
	common::Command makeNewUserCommand(int iUId, const std::string& cVersion, const std::string& userName, const std::string& password, const std::string& description);
	common::Command makeAskInfoCommand(int iUId);
	common::Command makeAskInfoCommand(int iUId, const std::vector<int>& iWIds);
	common::Command makeAskInfoCommand(int iUId, const std::string& organization);
	common::Command makeJSubmitCommand(int iUId, int iJid, const std::string& applicationName, const std::string& applicationVersion, int iPriority,
	                              int nCore, bool abortable, const std::string& averageTime, const std::string& maxTime, const std::string argument);
	common::Command makeJAbortCommand(int iUId, int JId);
	common::Command makeWSelectCommand(int iUId, const std::vector<int>& targets, int prioirty, int nMaxCore = 0);
	common::Command makeWSelectCommand(int iUId, const std::vector<Filter>& filters, int prioirty);
	common::Command makeJInCommand(int iUId, int iJId, const std::string& jobInput);
};

inline common::Command ClientCommandFactory::makeNewUserCommand(const std::string& cVersion, const std::string& userName, const std::string& password, const std::string& description)
{
	return makeCommand(COMMANDTYPE_NEW_USER, new NewUserData(0, cVersion, userName, password, description));
}

inline common::Command ClientCommandFactory::makeNewUserCommand(int iUId, const std::string& cVersion, const std::string& userName, const std::string& password, const std::string& description)
{
	return makeCommand(COMMANDTYPE_NEW_USER, new NewUserData(iUId, cVersion, userName, password, description));
}

inline common::Command ClientCommandFactory::makeAskInfoCommand(int iUId)
{
	return makeCommand(COMMANDTYPE_ASK_INFO, new AskInfoData(iUId));
}

inline common::Command ClientCommandFactory::makeAskInfoCommand(int iUId, const std::vector<int>& iWIds)
{
	return makeCommand(COMMANDTYPE_ASK_INFO, new AskInfoData(iUId, iWIds));
}

inline common::Command ClientCommandFactory::makeAskInfoCommand(int iUId, const std::string& organization)
{
	return makeCommand(COMMANDTYPE_ASK_INFO, new AskInfoData(iUId, organization));
}

inline common::Command ClientCommandFactory::makeJSubmitCommand(int iUId, int iJid, const std::string& applicationName, const std::string& applicationVersion, int iPriority,
                                int nCore, bool abortable, const std::string& averageTime, const std::string& maxTime, const std::string argument)
{
	return makeCommand(COMMANDTYPE_JSUBMIT, new JSubmitData(iUId, iJid, applicationName, applicationVersion, iPriority, nCore, abortable, averageTime, maxTime, argument));
}

inline common::Command ClientCommandFactory::makeJAbortCommand(int iUId, int iJId)
{
	return makeCommand(COMMANDTYPE_JABORT, new common::JAbortData(iUId, iJId));
}

inline common::Command ClientCommandFactory::makeWSelectCommand(int iUId, const std::vector<int>& iWIds, int iPriority, int nMaxCore)
{
	return makeCommand(COMMANDTYPE_WSELECT, new WSelectData(iUId, iWIds, iPriority, nMaxCore));
}

inline common::Command ClientCommandFactory::makeWSelectCommand(int iUId, const std::vector<Filter>& filters, int iPriority)
{
	return makeCommand(COMMANDTYPE_WSELECT, new WSelectData(iUId, filters, iPriority));
}

inline common::Command ClientCommandFactory::makeJInCommand(int iUId, int iJId, const std::string& jobInput)
{
	return makeCommand(COMMANDTYPE_JIN, new common::JInData(iUId, iJId, jobInput));
}

	}
}

#endif
