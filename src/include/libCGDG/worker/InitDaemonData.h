#ifndef INITDAEMONDATA_H
#define INITDAEMONDATA_H

#include "common/CommandData.h"
#include <string>

namespace cgdg
{
	namespace worker
	{

class InitDaemonData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	InitDaemonData();

	int getWId() const;
	const std::string& getDaemonRatio() const;
private:
	int m_iWId;
	std::string m_daemonRatio;
};

inline InitDaemonData::InitDaemonData()
: m_iWId(0), m_daemonRatio("")
{
}

inline int InitDaemonData::getWId() const
{
	return m_iWId;
}


inline const std::string& InitDaemonData::getDaemonRatio() const
{
	return m_daemonRatio;
}

	}
}

#endif
