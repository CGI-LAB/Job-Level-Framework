#ifndef REJECTUSERDATA_H
#define REJECTUSERDATA_H

#include "common/CommandData.h"

#include <string>

namespace cgdg
{
	namespace client
	{

class RejectUserData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	RejectUserData();
	const std::string& getBVersion() const;
	const std::string& getErrorCode() const;
	const std::string& getMessage() const;
private:
	std::string m_bVersion;
	std::string m_errorCode;
	std::string m_message;
};

inline RejectUserData::RejectUserData()
: m_bVersion(""), m_errorCode(""), m_message("")
{
}

inline const std::string& RejectUserData::getBVersion() const
{
	return m_bVersion;
}

inline const std::string& RejectUserData::getErrorCode() const
{
	return m_errorCode;
}

inline const std::string& RejectUserData::getMessage() const
{
	return m_message;
}

	}
}

#endif
