#ifndef JABORTACKDATA_H
#define JABORTACKDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace common
	{

class JAbortAckData : public common::CommandData
{
public:
	//for send command
	virtual void insertInto(TiXmlNode& parentNode) const;	
	JAbortAckData(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string& message);

	//for receive command
	virtual int fetch(const TiXmlNode& parentNode);			
	JAbortAckData();

	//getter
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

inline JAbortAckData::JAbortAckData()
: m_iJId(-1), m_iUId(-1), m_iWId(-1), m_errorCode(""), m_message("")
{
}

inline JAbortAckData::JAbortAckData(int iUId, int iJId, int iWId, const std::string& errorCode, const std::string& message)
: m_iUId(iUId), m_iJId(iJId), m_iWId(iWId), m_errorCode(errorCode), m_message(message)
{
}

inline int JAbortAckData::getUId() const
{
	return m_iUId;
}

inline int JAbortAckData::getJId() const
{
	return m_iJId;
}

inline int JAbortAckData::getWId() const
{
	return m_iWId;
}

inline const std::string& JAbortAckData::getErrorCode() const
{
	return m_errorCode;
}

inline const std::string& JAbortAckData::getMessage() const
{
	return m_message;
}

	}
}

#endif
