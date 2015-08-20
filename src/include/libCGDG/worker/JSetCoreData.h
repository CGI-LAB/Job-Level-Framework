#ifndef JSETCORE_H
#define JSETCORE_H

#include "common/CommandData.h"

/*
modify the cores of a job
1.	Broker sends Setcore to worker, in order to reduce some cores of a job by scheduler.
	Worker returns SetCoreAck
2.	Worker sends Setcore to Broker, tells Broker that it will reduce some cores of a job
	Broker returns SetCoreAck
@author	mikekao
@date	2014/02/26
*/
namespace cgdg 
{
	namespace worker
	{

class JSetCoreData : public common::CommandData 
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);
	
	JSetCoreData(int iUid, int iJid, int iWid, int iCore, int iSetCore);
	JSetCoreData();

	int getUId() const;
	int getJId() const;
	int getWId() const;
	int getCore() const;
	int getSetCore() const;
private:
	int m_iUId;
	int m_iJId;
	int m_iWId;
	int m_iCore;
	int m_iSetCore;
};

inline JSetCoreData::JSetCoreData(int iUid, int iJid, int iWid, int iCore, int iSetCore)
:m_iUId(iUid), m_iJId(iJid), m_iWId(iWid), m_iCore(iCore), m_iSetCore(iSetCore)
{
}

inline JSetCoreData::JSetCoreData()
	: m_iUId(-1), m_iJId(-1), m_iWId(-1), m_iCore(-1), m_iSetCore(-1)
{
}

inline int JSetCoreData::getUId() const
{
	return m_iUId;
}

inline int JSetCoreData::getJId() const
{
	return m_iJId;
}

inline int JSetCoreData::getWId() const
{
	return m_iWId;
}

inline int JSetCoreData::getCore() const
{
	return m_iCore;
}

inline int JSetCoreData::getSetCore() const
{
	return m_iSetCore;
}

	}	
}

#endif
