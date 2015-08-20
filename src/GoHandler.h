#ifndef JL_GOHANDLER_H
#define JL_GOHANDLER_H

#include "BaseGameHandler.h"
#include "GoJMsgParser.h"

namespace joblevel
{

class GoHandler : public BaseGameHandler
{
public:
	GoHandler();
	virtual ~GoHandler() {}
	std::string getAppName() const;
	std::string getAppVersion() const;
	std::string getArgument(NodePtr pNode) const;

protected:
	void setBfsPlayerColor(NodePtr pNode) const;

private:
	std::string getPath(NodePtr pNode) const;
	std::string getIgnoreMove(NodePtr pNode) const;

private:
	GoJMsgParser m_pGoJMsgParser;
};

}

#endif
