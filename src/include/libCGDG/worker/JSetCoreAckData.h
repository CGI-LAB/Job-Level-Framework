#ifndef JSETCOREACKDATA_H
#define JSETCOREACKDATA_H

#include "common/CommandData.h"
#include <cstring>

/*
modify the cores of a job
1.	Worker returns SetCoreAck to Broker
2.	Broker returns SetCoreAck to Worker
@author mikekao
@date	2014/02/26
*/
namespace cgdg 
{
	namespace worker
	{

class JSetCoreAckData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JSetCoreAckData(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& sErrorCode, const std::string& sMessage);
	JSetCoreAckData();

	int getUId() const;
	int getJId() const;
	int getWId() const;
	int getCore() const;
	int getSetCore() const;
	const std::string& getErrorCode() const;
	const std::string& getMessage() const;
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
	int m_iCore;
	int m_iSetCore;
	std::string m_sErrorCode;
	std::string m_sMessage;
};

inline JSetCoreAckData::JSetCoreAckData(int iUId, int iJId, int iWId, int iCore, int iSetCore, const std::string& sErrorCode, const std::string& sMessage)
: m_iUId(iUId), m_iJId(iJId), m_iWId(iWId), m_iCore(iCore), m_iSetCore(iSetCore), m_sErrorCode(sErrorCode), m_sMessage(sMessage)
{
}

inline JSetCoreAckData::JSetCoreAckData()
:m_iUId(-1), m_iJId(-1), m_iWId(-1), m_iCore(-1), m_iSetCore(-1), m_sErrorCode(""), m_sMessage("")
{
}

inline int JSetCoreAckData::getUId() const
{
	return m_iUId;
}

inline int JSetCoreAckData::getJId() const
{
	return m_iJId;
}

inline int JSetCoreAckData::getWId() const
{
	return m_iWId;
}

inline int JSetCoreAckData::getCore() const
{
	return m_iCore;
}

inline int JSetCoreAckData::getSetCore() const
{
	return m_iSetCore;
}

inline const std::string& JSetCoreAckData::getErrorCode() const
{
	return m_sErrorCode;
}

inline const std::string& JSetCoreAckData::getMessage() const
{
	return m_sMessage;
}

	}
}

#endif
