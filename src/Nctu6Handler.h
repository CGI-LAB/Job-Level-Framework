#ifndef JL_NCTU6HANDLER_H
#define JL_NCTU6HANDLER_H

#include "GameHandler.h"
#include "Nctu6Parser.h"

namespace joblevel 
{

class Nctu6Handler : public GameHandler
{
public:
	Nctu6Handler();
	virtual ~Nctu6Handler() {}
	std::string getAppName() const;
	std::string getAppVersion() const;
	std::string prepareJobCommands(NodePtr pNode) const;
	bool handleDuplicateNode(NodePtr pNode) const;

protected:
	void setBfsPlayerColor(NodePtr pNode) const;

private:
	std::string getPath(NodePtr pNode) const;
	std::string getIgnoreMove(NodePtr pNode) const;

private:
	Nctu6Parser m_pConnect6JMsgParser;
};

} // joblevel

#endif // JL_CONNECT6HANDLER_H
