#ifndef JMSGDATA_H
#define JMSGDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace common
	{

class JMsgData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JMsgData();
	JMsgData(int iUId, int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage);
	int getUId() const;
	int getJId() const;
	int getWId() const;
	const std::string& getApplicationName() const;
	const std::string& getApplicationVersion() const;
	const std::string& getJobMessage() const;
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
	std::string m_applicationName;
	std::string m_applicationVersion;
	std::string m_jobMessage;
};

inline JMsgData::JMsgData()
: m_iUId(-1), m_iJId(-1), m_iWId(-1), m_applicationName(""), m_applicationVersion(""), m_jobMessage("")
{
}

inline JMsgData::JMsgData(int iUId, int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage)
: m_iUId(iUId), m_iJId(iJId), m_iWId(iWId), m_applicationName(applicationName), m_applicationVersion(applicationVersion), m_jobMessage(jobMessage)
{
}

inline int JMsgData::getUId() const
{
	return m_iUId;
}

inline int JMsgData::getJId() const
{
	return m_iJId;
}

inline int JMsgData::getWId() const
{
	return m_iWId;
}

inline const std::string& JMsgData::getApplicationName() const
{
	return m_applicationName;
}

inline const std::string& JMsgData::getApplicationVersion() const
{
	return m_applicationVersion;
}

inline const std::string& JMsgData::getJobMessage() const
{
	return m_jobMessage;
}

	}
}

#endif
