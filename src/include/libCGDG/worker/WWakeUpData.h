#ifndef WWAKEUPDATA_H
#define WWAKEUPDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace worker
	{

class WWakeUpData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	WWakeUpData(int iWId);

private:
	int m_iWId;
};


inline int WWakeUpData::fetch(const TiXmlNode& parentNode)
{
	assert(false);
	return -1;
}

inline WWakeUpData::WWakeUpData(int iWId) :
m_iWId(iWId)
{
}

	}
}

#endif
