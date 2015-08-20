#ifndef WSELECTDATA_H
#define WSELECTDATA_H

#include "common/CommandData.h"

#include "client/CompositeType.h"
#include <vector>

namespace cgdg
{
	namespace client
	{

class WSelectData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	WSelectData(int iUId, const std::vector<int>& iWIds, int iPriority, int nMaxCores = 0);
	WSelectData(int iUId, const std::vector<Filter>& filters, int iPriority);
private:
	static void insert(TiXmlNode& filterNode, const Filter& filter);

	int m_iUId;
	std::vector<int> m_iWIds;
	std::vector<Filter> m_filters;
	int m_iPriority;
	int m_nMaxCores;
};

inline WSelectData::WSelectData(int iUId, const std::vector<int>& iWIds, int iPriority, int nMaxCores)
: m_iUId(iUId), m_iWIds(iWIds), m_iPriority(iPriority), m_nMaxCores(nMaxCores)
{
}

inline WSelectData::WSelectData(int iUId, const std::vector<Filter>& filters, int iPriority)
: m_iUId(iUId), m_filters(filters), m_iPriority(iPriority), m_nMaxCores(0)
{
}

	}
}

#endif
