#ifndef JNEXTDATA_H
#define JNEXTDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace client
	{

class JNextData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JNextData();
	int getUId() const;
private:
	int m_iUId;
};

inline JNextData::JNextData()
: m_iUId(-1)
{
}

inline int JNextData::getUId() const
{
	return m_iUId;
}

	}
}

#endif
