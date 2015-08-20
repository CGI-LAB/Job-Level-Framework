#ifndef WLOSTDATA_H
#define WLOSTDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace client
	{

class WLostData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	WLostData();

	int getUId() const;
	int getWId() const;
private:
	int m_iUId;
	int m_iWId;
};

inline WLostData::WLostData()
: m_iUId(0), m_iWId(0)
{
}

inline int WLostData::getUId() const
{
	return m_iUId;
}

inline int WLostData::getWId() const
{
	return m_iWId;
}

	}
}

#endif
