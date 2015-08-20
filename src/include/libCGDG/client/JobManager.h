#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <vector>
#include <queue>
#include <string>
#include <cassert>
#include <algorithm>

namespace cgdg
{
	namespace client
	{

enum JobStatus
{
	JOBSTATUS_WAITING,
	JOBSTATUS_SUBMITDONE,
	JOBSTATUS_ASSIGNDONE,
	JOBSTATUS_DOING,
	JOBSTATUS_DONE,
	JOBSTATUS_FAIL,
	JOBSTATUS_DROP,
	JOBSTATUS_ABORT
};

struct SubmitInformation
{
	std::string m_applicationName;
	std::string m_applicationVersion;
	int m_iPriority;
	int m_nCore;
	bool m_bIsAbortable;
	std::string m_averageTime;
	std::string m_maxTime;
	std::string m_argument;
};

struct OwnedJob
{
	int m_iJId;
	JobStatus m_jobStatus;
	SubmitInformation m_submitInformation;
};

class GridSystem;

class JobManager
{
public:
	JobManager();

	virtual void updateJobStatus(int iJId, JobStatus jobStatus);
	virtual void remove(int iJId);
	virtual void clear();
	const OwnedJob* getJob(int iJId) const;
	const std::vector<OwnedJob>& getJobList() const;

	int pushJob(const SubmitInformation& submitInformation);
	int getFrontJobId() const;
	int getWaitingJobCount() const;
	void popJob();
	bool hasWaitingJob() const;
	void requeueUndoneJobs();
protected:
	virtual void add(const OwnedJob& jobInformation);

private:
	std::vector<OwnedJob> m_jobList;

	int m_iJobSerial;
	std::queue<int> m_jobQueue;
};

inline JobManager::JobManager()
: m_iJobSerial(1)
{
}

inline void JobManager::add(const OwnedJob& jobInformation)
{
	m_jobList.push_back(jobInformation);
}

inline void JobManager::clear()
{
	m_jobList.clear();
	std::queue<int> emptyQueue;
	m_jobQueue = emptyQueue;
}

inline const std::vector<OwnedJob>& JobManager::getJobList() const
{
	return m_jobList;
}

inline int JobManager::pushJob(const SubmitInformation& submitInformation)
{
	OwnedJob jobInformation;
	jobInformation.m_iJId = m_iJobSerial;
	jobInformation.m_jobStatus = JOBSTATUS_WAITING;
	jobInformation.m_submitInformation = submitInformation;
	add(jobInformation);
	m_jobQueue.push(jobInformation.m_iJId);
	return m_iJobSerial++;
}

inline int JobManager::getFrontJobId() const
{
	assert(!m_jobQueue.empty());
	return m_jobQueue.front();
}

inline void JobManager::popJob()
{
	m_jobQueue.pop();
}

inline bool JobManager::hasWaitingJob() const
{
	return !m_jobQueue.empty();
}

inline int JobManager::getWaitingJobCount() const
{
	return static_cast<int>(m_jobQueue.size());
}

	}
}

#endif
