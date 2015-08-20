#ifndef ASKINFODATA_H
#define ASKINFODATA_H

#include "common/CommandData.h"

#include <string>
#include <vector>

namespace cgdg
{
	namespace client
	{

class AskInfoData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	AskInfoData(int iUId);
	AskInfoData(int iUId, const std::vector<int>& iWIds);
	AskInfoData(int iUId, const std::string& organization);
private:
	int m_iUId;
	std::vector<int> m_iWIds;
	std::string m_organization;
};



inline AskInfoData::AskInfoData(int iUId)
: m_iUId(iUId), m_iWIds(), m_organization("")
{
}

inline AskInfoData::AskInfoData(int iUId, const std::vector<int>& iWIds)
: m_iUId(iUId), m_iWIds(iWIds), m_organization("")
{
}

inline AskInfoData::AskInfoData(int iUId, const std::string& organization)
: m_iUId(iUId), m_iWIds(), m_organization(organization)
{
}
	}
}

#endif
