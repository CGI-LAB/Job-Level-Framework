#ifndef INITUSERDATA_H
#define INITUSERDATA_H

#include "common/CommandData.h"

#include <string>

namespace cgdg
{
	namespace client
	{

class InitUserData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	InitUserData();
	int getUId() const;
	const std::string& getBVersion() const;
	const std::string& getErrorCode() const;
	const std::string& getMessage() const;
private:
	int m_iUId;
	std::string m_bVersion;
	std::string m_errorCode;
	std::string m_message;
};

inline InitUserData::InitUserData()
: m_iUId(-1), m_bVersion(""), m_errorCode(""), m_message("")
{
}

inline int InitUserData::getUId() const
{
	return m_iUId;
}

inline const std::string& InitUserData::getBVersion() const
{
	return m_bVersion;
}

inline const std::string& InitUserData::getErrorCode() const
{
	return m_errorCode;
}

inline const std::string& InitUserData::getMessage() const
{
	return m_message;
}

	}
}

#endif
