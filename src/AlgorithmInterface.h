#ifndef JL_ALGORITHMINTERFACE
#define JL_ALGORITHMINTERFACE

#include <string>
#include "Node.h"
#include "JobLevelMiddleware.h"

namespace joblevel
{
/*!
	@brief	Algorithm interface for develop on top of job-level middleware
	@author	chaochin
	@date	2015/7/23
 */
class AlgorithmInterface
{
public:
	AlgorithmInterface() {}
	virtual ~AlgorithmInterface() {}

	void setJobLevelMiddleware(JobLevelMiddleware* jobLevelMiddleware)
	{
		m_jobLevelMiddleware = jobLevelMiddleware;
	}
	////////////////////////////////////////
	// APIs need to inherit and implement //
	////////////////////////////////////////
	/*!
		@brief	initialize is used to initialize the algorithm with initial data
		@param  pNode	the root of job-level search tree
		@return	true if successful
	 */		
	virtual bool initialize(NodePtr pNode) = 0;
	/*!
		@brief	Request jobs to submit
		@return	true if successful
	 */		
	virtual bool requestJobs() = 0;
	/*!
		@brief	Handle job message
		@param	iJId	the ID of received job
		@param	pNode	the node whtch submit the job
		@param	sMessage	returning message of the job
	 */		
	virtual void receiveJobMessage(int iJId, NodePtr pNode, const std::string& sMessage) = 0;
	/*!
		@brief	Check whether the algorithm is finished
		@return	true if the algorithm is finished
	 */		
	virtual bool isCompleted() = 0;
	/*!
		@brief	Finalize the algorithm, like print finish message and time
	 */		
	virtual void finalize() = 0;

protected:
	/*!
		@brief	Used to submit job with a node
		@param	pNode	the node to submit job
		@param	sApplicationName	the app name of the job
		@param	sApplicationVersion	the app version of the job
		@param	sArgument	the job arguments
		@return	job ID of the job
	 */		
	int submitJob(NodePtr pNode, const std::string& sApplicationName,
		const std::string& sApplicationVersion, const std::string& sArgument)
	{
		return m_jobLevelMiddleware->submitJob(pNode, sApplicationName,
			sApplicationVersion, sArgument);
	}
	/*!
		@brief	Send standart input to the running job
		@param	pNode	the node to send job input
		@param	iJId	the job ID that send job input to
		@param	sJobInput	job input to send
		@return	error code, 0 if success
	 */		
	int sendJobinput(NodePtr pNode, int iJId, const std::string& sJobInput)
	{
		return m_jobLevelMiddleware->sendJobinput(pNode, iJId, sJobInput);
	}
	/*!
		@brief	abort job with job ID
		@param	iJId	the job ID to abort
		@return	error code, 0 if success
	 */		
	int abortJob(int iJId)
	{
		return m_jobLevelMiddleware->abortJob(iJId);
	}
	/*!
		@brief	check if there are some waiting jobs, that means some jobs are
				stored in the queue and wait to submit to broker
		@return	true if has waiting jobs
	 */		
	bool hasWaitingJob()
	{
		return m_jobLevelMiddleware->hasWaitingJob();
	}

private:
	JobLevelMiddleware* m_jobLevelMiddleware; //<!	pointer of middleware, for down call to middleware
};

}

#endif
