#ifndef JASSIGNDONEDATA_H
#define JASSIGNDONEDATA_H

#include "common/CommandData.h"

#include <string>

namespace cgdg
{
	namespace client
	{

class JAssignDoneData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JAssignDoneData();
	int getUId() const;
	int getJId() const;
private:
	int m_iUId;
	int m_iJId;
};

inline JAssignDoneData::JAssignDoneData()
: m_iUId(0), m_iJId(0)
{
}

inline int JAssignDoneData::getUId() const
{
	return m_iUId;
}

inline int JAssignDoneData::getJId() const
{
	return m_iJId;
}

	}
}

#endif
