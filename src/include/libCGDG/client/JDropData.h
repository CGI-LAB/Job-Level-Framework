#ifndef JDROPDATA_H
#define JDROPDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace client
	{

class JDropData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JDropData();
	int getUId() const;
	int getJId() const;
	int getWId() const;
	const std::string& getErrorCode() const;
	const std::string& getMessage() const;
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
	std::string m_errorCode;
	std::string m_message;
};

inline JDropData::JDropData()
: m_iUId(-1), m_iJId(-1), m_iWId(-1), m_errorCode(""), m_message("")
{
}

inline int JDropData::getUId() const
{
	return m_iUId;
}

inline int JDropData::getJId() const
{
	return m_iJId;
}

inline int JDropData::getWId() const
{
	return m_iWId;
}

inline const std::string& JDropData::getErrorCode() const
{
	return m_errorCode;
}

inline const std::string& JDropData::getMessage() const
{
	return m_message;
}

	}
}

#endif
