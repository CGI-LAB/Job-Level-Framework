#ifndef WSLEEPDATA_H
#define WSLEEPDATA_H

#include "common/CommandData.h"
#include <cassert>

namespace cgdg
{
	namespace worker
	{

class WSleepData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	WSleepData(int iWId);

private:
	int m_iWId;
};

inline int WSleepData::fetch(const TiXmlNode& parentNode)
{
	assert(false);
	return -1;
}

inline WSleepData::WSleepData(int iWId) :
m_iWId(iWId)
{
}

	}
}

#endif
