#ifndef CLIENT_JOBHANDLERINTERFACE_H
#define CLIENT_JOBHANDLERINTERFACE_H

namespace cgdg
{
	namespace client
	{

class JobHandlerInterface
{
public:
	//job
	virtual void handleSubmissionResult(int iJId, const std::string& errorCode, const std::string& message) = 0;
	virtual void handleJobSendingAvaliable() = 0;
	virtual void handleJobMsg(int iJId, int iWId, const std::string& applicationName, const std::string& applicationVersion, const std::string& jobMessage) = 0;
	virtual void handleJobDone(int iJId, int iWId, const std::string& sTime, const std::string& uTime, const std::string& kTime) = 0;
	virtual void handleJobFail(int iJId, int iWId) = 0;
	virtual void handleJobDrop(int iJId, int iWId) = 0;
	virtual void handleJobDoing(int iJId, int iWId) = 0;
	virtual void handleJobAssignDone(int iJId) = 0;
	virtual void handleJobAbortAck(int iJId, int iWId, const std::string& errorCode, const std::string& message) = 0;
};

	}
}

#endif
