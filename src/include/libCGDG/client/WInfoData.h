#ifndef WINFODATA_H
#define WINFODATA_H

#include "common/CommandData.h"
#include "CompositeType.h"

namespace cgdg
{
	namespace client
	{

class WInfoData : public common::CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const;
	virtual int fetch(const TiXmlNode& parentNode);

	WInfoData();
	int getUId() const;
	const WorkerStatus& getWorkerStatus() const;
private:
	static void insert(TiXmlNode& filterNode, const Job& job);
	using CommandData::insert;

	int m_iUId;
	WorkerStatus m_workerStatus;
};

inline WInfoData::WInfoData()
: m_iUId(-1)
{
}

inline int WInfoData::getUId() const
{
	return m_iUId;
}

inline const WorkerStatus& WInfoData::getWorkerStatus() const
{
	return m_workerStatus;
}

	}
}

#endif
