#ifndef JINDATA_H
#define JINDATA_H

#include "common/CommandData.h"

namespace cgdg
{
	namespace common
	{

class JInData : public CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	JInData();
	JInData(int iUId, int iJId, const std::string& jobMessage);
	int getUId() const;
	int getJId() const;
	const std::string& getJobInput() const;
private:
	int m_iUId;
	int m_iJId;
	std::string m_jobInput;
};

inline JInData::JInData() :
m_iUId(0), m_iJId(-1), m_jobInput("")
{
}

inline JInData::JInData(int iUId, int iJId, const std::string& jobMessage) :
m_iUId(iUId), m_iJId(iJId), m_jobInput(jobMessage)
{
}

inline int JInData::getUId() const
{
	return m_iUId;
}

inline int JInData::getJId() const
{
	return m_iJId;
}

inline const std::string& JInData::getJobInput() const
{
	return m_jobInput;
}

	}
}

#endif
