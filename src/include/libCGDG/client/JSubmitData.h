#ifndef JSUBMITDATA_H
#define JSUBMITDATA_H

#include "common/CommandData.h"

#include "client/CompositeType.h"
#include <string>

namespace cgdg
{
	namespace client
	{

class JSubmitData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JSubmitData(int iUId, int iJid, const std::string& applicationName, const std::string& applicationVersion, int iPrioirty,
		int nCore, bool bAbortable, const std::string& averageTime, const std::string& maxTime, const std::string& argument);
private:
	int m_iUId;
	int m_iJid;
	std::string m_applicationName;
	std::string m_applicationVersion;
	int m_iPriority;
	int m_nCore;
	bool m_bAbortable;
	std::string m_averageTime;
	std::string m_maxTime;
	std::string m_argument;
};

inline JSubmitData::JSubmitData(int iUId, int iJid, const std::string& applicationName, const std::string& applicationVersion, int iPriority,
								int nCore, bool bAbortable, const std::string& averageTime, const std::string& maxTime, const std::string& argument)
: m_iUId(iUId), m_iJid(iJid), m_applicationName(applicationName), m_applicationVersion(applicationVersion), m_iPriority(iPriority),
  m_nCore(nCore), m_bAbortable(bAbortable), m_averageTime(averageTime), m_maxTime(maxTime), m_argument(argument)
{
}

	}
}

#endif
