#ifndef JASSIGNDATA_H
#define JASSIGNDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace worker
	{

class JAssignData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JAssignData();
	int getUId() const;
	int getJId() const;
	int getWId() const;
	const std::string& getApplicationName() const;
	const std::string& getApplicationVersion() const;
	int getCoreNumber() const;
	const std::string& getArgument() const;
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
	std::string m_applicationName;
	std::string m_applicationVersion;
	int m_nCore;
	std::string m_argument;
};

inline JAssignData::JAssignData()
: m_iUId(0), m_iJId(-1), m_iWId(0), m_applicationName(""), m_applicationVersion(""), m_nCore(0), m_argument("")
{
}


inline int JAssignData::getUId() const
{
	return m_iUId;
}

inline int JAssignData::getJId() const
{
	return m_iJId;
}

inline int JAssignData::getWId() const
{
	return m_iWId;
}

inline const std::string& JAssignData::getApplicationName() const
{
	return m_applicationName;
}

inline const std::string& JAssignData::getApplicationVersion() const
{
	return m_applicationVersion;
}

inline int JAssignData::getCoreNumber() const
{
	return m_nCore;
}

inline const std::string& JAssignData::getArgument() const
{
	return m_argument;
}


	}
}

#endif
