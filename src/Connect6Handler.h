#ifndef JL_CONNECT6HANDLER_H
#define JL_CONNECT6HANDLER_H

#include "BaseGameHandler.h"
#include "Connect6JMsgParser.h"

namespace joblevel 
{

class Connect6Handler : public BaseGameHandler
{
public:
	Connect6Handler();
	virtual ~Connect6Handler() {}
	std::string getAppName() const;
	std::string getAppVersion() const;
	std::string getArgument(NodePtr pNode) const;
	bool handleDuplicateNode(NodePtr pNode) const;

protected:
	void setBfsPlayerColor(NodePtr pNode) const;

private:
	std::string getPath(NodePtr pNode) const;
	std::string getIgnoreMove(NodePtr pNode) const;

private:
	Connect6JMsgParser m_pConnect6JMsgParser;
};

} // joblevel

#endif // JL_CONNECT6HANDLER_H
