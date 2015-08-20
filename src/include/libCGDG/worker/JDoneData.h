#ifndef WORKER_JDONEDATA_H
#define WORKER_JDONEDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace worker
	{

class JDoneData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JDoneData(int iUId, int iJId, int iWId, const std::string& uTime, const std::string& kTime);
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
	std::string m_uTime;
	std::string m_kTime;
};

inline JDoneData::JDoneData(int iUId, int iJId, int iWId, const std::string& uTime, const std::string& kTime)
: m_iUId(iUId), m_iJId(iJId), m_iWId(iWId), m_uTime(uTime), m_kTime(kTime)
{
}

	}
}

#endif
