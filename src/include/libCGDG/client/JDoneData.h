#ifndef CLIENT_JDONEDATA_H
#define CLIENT_JDONEDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace client
	{

class JDoneData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JDoneData();
	int getUId() const;
	int getJId() const;
	int getWId() const;
	const std::string& getSTime() const;
	const std::string& getUTime() const;
	const std::string& getKTime() const;
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
	std::string m_sTime;
	std::string m_uTime;
	std::string m_kTime;
};

inline JDoneData::JDoneData()
: m_iUId(0), m_iJId(-1), m_iWId(0), m_sTime(""), m_uTime(""), m_kTime("")
{
}

inline int JDoneData::getUId() const
{
	return m_iUId;
}

inline int JDoneData::getJId() const
{
	return m_iJId;
}

inline int JDoneData::getWId() const
{
	return m_iWId;
}

inline const std::string& JDoneData::getSTime() const
{
	return m_sTime;
}

inline const std::string& JDoneData::getUTime() const
{
	return m_uTime;
}

inline const std::string& JDoneData::getKTime() const
{
	return m_kTime;
}

	}
}

#endif
