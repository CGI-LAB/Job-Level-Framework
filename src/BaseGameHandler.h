#ifndef JL_BASEGAMEHANDLER_H
#define JL_BASEGAMEHANDLER_H

#include <string>
#include <sstream>
#include "Node.h"
#include "BaseMove.h"

namespace joblevel
{

class BaseJMsgParser;
/*!
	@brief	Base game handler used in base BFS algorithm, mainly for expanding
			new node and setting up data from the result. Futhermore, implement
			different behavior of each game such as solving GHI problem for Go.
	@author	chaochin
	@date	2015/7/22
 */
class BaseGameHandler
{
public:
	BaseGameHandler();
	virtual ~BaseGameHandler() {}
	BaseJMsgParser* getBaseJMsgParser() const;
	virtual void initializeNode(NodePtr pNode) const;
	/////////////////////////////////
	// Functions need to implement //
	/////////////////////////////////
	virtual std::string getAppName() const = 0;
	virtual std::string getAppVersion() const = 0;
	virtual std::string getArgument(NodePtr pNode) const = 0;

	bool isNodeAlreadyExist(NodePtr pNode, const std::string& sResult) const;
	NodePtr generateNode(NodePtr pNode, const std::string& sResult) const;
	////////////////////////////////////////////////
	// Some pre-defined behavior, can be override //
	////////////////////////////////////////////////
	virtual void setupGameData(NodePtr pNode, const std::string& sResult) const;
	virtual bool handleDuplicateNode(NodePtr pNode) const;

protected:
	void setBaseJMsgParser(BaseJMsgParser* pBaseJMsgParser);
	virtual void setBfsPlayerColor(NodePtr pNode) const = 0;

private:
	BaseJMsgParser* m_pBaseJMsgParser;
};

}

#endif
