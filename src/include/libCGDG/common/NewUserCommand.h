#ifndef NEWUSERCOMMAND_H
#define NEWUSERCOMMAND_H

#include "Command.h"

namespace cgdg
{
	namespace client
	{

class NewUserCommand : public common::Command
{
public:
	virtual std::string getXml() const;
	virtual CommandType getCommandType() const;
};

	}
}

#endif
