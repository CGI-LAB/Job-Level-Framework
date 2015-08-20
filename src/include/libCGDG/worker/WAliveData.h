#ifndef WALIVEDATA_H
#define WALIVEDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace worker
	{

class WAliveData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	WAliveData(
		int iWId,
		int nCoreNum,
		int nCoreUsed,
		unsigned cpuSpeed, // in MHz
		unsigned cpuUsage, // in %
		unsigned ramSize, // in MB
		unsigned ramUsage, // in %
		double inops, // in operations/second
		double flops // in operations/second
	);
private:
	int m_iWId;
	int m_nCoreNum;
	int m_nCoreUsed;
	unsigned m_cpuSpeed;
	unsigned m_cpuUsage;
	unsigned m_ramSize;
	unsigned m_ramUsage;
	double m_inops;
	double m_flops;
};

inline WAliveData::WAliveData(
	int iWId,
	int nCoreNum,
	int nCoreUsed,
	unsigned cpuSpeed, // in MHz
	unsigned cpuUsage, // in %
	unsigned ramSize, // in MB
	unsigned ramUsage, // in %
	double inops, // in operations/second
	double flops // in operations/second
) :
m_iWId(iWId), 
m_nCoreNum(nCoreNum),
m_nCoreUsed(nCoreUsed),
m_cpuSpeed(cpuSpeed),
m_cpuUsage(cpuUsage),
m_ramSize(ramSize),
m_ramUsage(ramUsage),
m_inops(inops),
m_flops(flops)
{
}

	}
}

#endif
