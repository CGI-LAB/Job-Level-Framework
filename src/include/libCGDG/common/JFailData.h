#ifndef JFAILDATA_H
#define JFAILDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace common
	{

class JFailData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JFailData();
	JFailData(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string message);
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

inline JFailData::JFailData()
: m_iUId(0), m_iJId(-1), m_iWId(0), m_errorCode(""), m_message("")
{
}

inline JFailData::JFailData(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string message)
: m_iUId(iUId), m_iJId(iJId), m_iWId(iWId), m_errorCode(errorCode), m_message(message)
{
}

inline int JFailData::getUId() const
{
	return m_iUId;
}

inline int JFailData::getJId() const
{
	return m_iJId;
}

inline int JFailData::getWId() const
{
	return m_iWId;
}

inline const std::string& JFailData::getErrorCode() const
{
	return m_errorCode;
}

inline const std::string& JFailData::getMessage() const
{
	return m_message;
}

	}
}

#endif
