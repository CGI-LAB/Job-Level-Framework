#ifndef JL_GAMEHANDLER_H
#define JL_GAMEHANDLER_H

#include <string>
#include <sstream>
#include "Node.h"
#include "BaseMove.h"

namespace joblevel
{

class GameParser;
/*!
	@brief	Base game handler used in base BFS algorithm, mainly for expanding
			new node and setting up data from the result. Futhermore, implement
			different behavior of each game such as solving GHI problem for Go.
	@author	chaochin
	@date	2015/7/22
 */
class GameHandler
{
public:
	GameHandler();
	virtual ~GameHandler() {}
	GameParser* getBaseJMsgParser() const;
	virtual void initializeNode(NodePtr pNode) const;
	/////////////////////////////////
	// Functions need to implement //
	/////////////////////////////////
	virtual std::string getAppName() const = 0;
	virtual std::string getAppVersion() const = 0;
	virtual std::string prepareJobCommands(NodePtr pNode) const = 0;

	bool isNodeAlreadyExist(NodePtr pNode, const std::string& sResult) const;
	NodePtr generateNode(NodePtr pNode, const std::string& sResult) const;
	////////////////////////////////////////////////
	// Some pre-defined behavior, can be override //
	////////////////////////////////////////////////
	virtual void setupGameData(NodePtr pNode, const std::string& sResult) const;
	virtual bool handleDuplicateNode(NodePtr pNode) const;

protected:
	void setBaseJMsgParser(GameParser* pBaseJMsgParser);
	virtual void setBfsPlayerColor(NodePtr pNode) const = 0;

private:
	GameParser* m_pBaseJMsgParser;
};

}

#endif
