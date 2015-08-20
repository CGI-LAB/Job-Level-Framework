#ifndef CLIENT_BROKERAGENT_H
#define CLIENT_BROKERAGENT_H

#include "client/HandlerInterface.h"
#include "client/OperationInterface.h"
#include "common/NonblockingIOInterface.h"
#include "common/Command.h"
#include "common/BaseBrokerAgent.h"
#include "client/ClientCommandFactory.h"

#include <queue>

namespace cgdg
{
	namespace client
	{

class BrokerAgent : public common::BaseBrokerAgent, public OperationInterface
{
public:
	enum {
		ERRORCODE_NOTLOGIN = ERRORCODE_BLOCK + 1,
		ERRORCODE_HAVELOGGEDIN
	};

	BrokerAgent();

	void setHandler(HandlerInterface* pHandler);
	HandlerInterface* getHandler();

	bool isLogin() const;

	//Operation
	virtual int login(const std::string& userName, const std::string& password, const std::string& description);
	virtual int recheckIn();
	virtual int logout();
	virtual int updateWorkerInfo(const std::vector<int>& iWIds);
	virtual int updateWorkerInfo(const std::string& organization);
	virtual int updateWorkerInfo();
	virtual int selectWorker(const std::vector<int>& targets, int iPrioirty, int nMaxCore);
	virtual int selectWorker(const std::vector<Filter>& filters, int iPrioirty);
	virtual int submitJob(int iJId, const std::string& applicationName, const std::string& applicationVersion, int iPrioirty,
	                      int nCores, bool bIsAbortable, const std::string& averageTime, const std::string& maxTime, const std::string& argument);
	virtual int abortJob(int iJId);
	virtual int sendJobinput(int iJId, const std::string& jobInput);

protected:
	virtual void preprocess(const common::Command& command);
	virtual ErrorCode dispatch(const common::Command& command);
	ClientCommandFactory& getCommandFactory();

private:
	static const std::string C_VERSION;
	static const std::string B_VERSION;

	BrokerAgent(const BrokerAgent&);
	BrokerAgent& operator=(const BrokerAgent&);

	int m_iUId;

	std::string m_userName;
	std::string m_password;
	std::string m_description;

	ClientCommandFactory m_commandFactory;

	HandlerInterface* m_pHandler;
};

inline void BrokerAgent::setHandler(HandlerInterface* pHandler)
{
	assert(pHandler != NULL);
	BaseBrokerAgent::setHandler(pHandler);
	m_pHandler = pHandler;
}


inline bool BrokerAgent::isLogin() const
{
	return m_iUId != 0;
}

inline ClientCommandFactory& BrokerAgent::getCommandFactory()
{
	return m_commandFactory;
}

	}
}

#endif
