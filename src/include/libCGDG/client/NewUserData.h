#ifndef NEWUSERDATA_H
#define NEWUSERDATA_H

#include "common/CommandData.h"

#include <string>

namespace cgdg
{
	namespace client
	{

class NewUserData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	NewUserData(int iUId, const std::string& cVersion, const std::string& userName, const std::string& password, const std::string description);
private:
	int m_iUId;
	std::string m_cVersion;
	std::string m_userName;
	std::string m_password;
	std::string m_description;
};

inline NewUserData::NewUserData(int iUId, const std::string& cVersion, const std::string& userName, const std::string& password, const std::string description)
: m_iUId(iUId), m_cVersion(cVersion), m_userName(userName), m_password(password), m_description(description)
{
}

	}
}

#endif
