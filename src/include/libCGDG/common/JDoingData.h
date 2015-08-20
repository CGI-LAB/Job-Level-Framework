#ifndef JDOINGDATA_H
#define JDOINGDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace common
	{

class JDoingData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JDoingData();
	JDoingData(int iUId, int iJId, int iWId);
	int getUId() const;
	int getJId() const;
	int getWId() const;
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
};

inline JDoingData::JDoingData()
: m_iUId(-1), m_iJId(-1), m_iWId(-1)
{
}

inline JDoingData::JDoingData(int iUId, int iJId, int iWId)
: m_iUId(iUId), m_iJId(iJId), m_iWId(iWId)
{
}

inline int JDoingData::getUId() const
{
	return m_iUId;
}

inline int JDoingData::getJId() const
{
	return m_iJId;
}

inline int JDoingData::getWId() const
{
	return m_iWId;
}

	}
}

#endif
