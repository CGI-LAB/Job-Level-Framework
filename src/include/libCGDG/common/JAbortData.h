#ifndef JABORTDATA_H
#define JABORTDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace common
	{

class JAbortData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JAbortData();
	JAbortData(int iUId, int iJId);

	int getUId() const;
	int getJId() const;
private:
	int m_iUId;
	int m_iJId;
};

inline JAbortData::JAbortData()
: m_iUId(-1), m_iJId(-1)
{
}

inline JAbortData::JAbortData(int iUId, int iJId)
: m_iUId(iUId), m_iJId(iJId)
{
}

inline int JAbortData::getUId() const
{
	return m_iUId;
}

inline int JAbortData::getJId() const
{
	return m_iJId;
}

	}
}

#endif
