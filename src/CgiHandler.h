#ifndef JL_CGIHANDLER_H
#define JL_CGIHANDLER_H

#include "GameHandler.h"
#include "CgiParser.h"

namespace joblevel
{

class CgiHandler : public GameHandler
{
public:
	CgiHandler();
	virtual ~CgiHandler() {}
	virtual GameParser* makeGameParser(const std::string& sResult) const;
	std::string getAppName() const;
	std::string getAppVersion() const;
	std::string prepareJobCommands(NodePtr pNode) const;

protected:
	void setBfsPlayerColor(NodePtr pNode) const;

private:
	std::string getPath(NodePtr pNode) const;
	std::string getIgnoreMove(NodePtr pNode) const;
};

}

#endif
