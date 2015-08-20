#ifndef WORKERMANAGER_H
#define WORKERMANAGER_H

#include <vector>
#include <string>
#include "CompositeType.h"
#include <set>

namespace cgdg
{
	namespace client
	{

class WorkerManager
{
public:
	virtual void update(const WorkerStatus& workerStatus);
	virtual void updateUsage(int iWId, int nCoreUsed, const std::string& cpuUsage, const std::string& ramUsage, const std::string& description);
	virtual void setSelected(int iWId, bool isSelected);
	virtual void setAllSelected(bool isSelected);
	bool isSelected(int iWId);
	virtual void remove(int iWId);
	virtual void clear();
	const std::vector<WorkerStatus>& getWorkerList() const;
	int getUsedCoreCount() const;
	int getAvailableCoreCount() const;
	int getCoreCount() const;
private:
	std::vector<WorkerStatus> m_workerList;
	std::set<int> m_selectedWorkerIds;
};

inline const std::vector<WorkerStatus>& WorkerManager::getWorkerList() const
{
	return m_workerList;
}

inline bool WorkerManager::isSelected(int iWId)
{
	return m_selectedWorkerIds.find(iWId) != m_selectedWorkerIds.end();
}

inline void WorkerManager::setSelected(int iWId, bool isSelected)
{
	if (isSelected) m_selectedWorkerIds.insert(iWId);
	else m_selectedWorkerIds.erase(iWId);
}

inline void WorkerManager::setAllSelected(bool isSelected)
{
	for (std::vector<WorkerStatus>::const_iterator i = m_workerList.begin(); i != m_workerList.end(); ++i) {
		if (isSelected) m_selectedWorkerIds.insert(i->m_iWId);
		else m_selectedWorkerIds.erase(i->m_iWId);
	}
}

inline void WorkerManager::clear()
{
	m_workerList.clear();
};

	}
}

#endif
