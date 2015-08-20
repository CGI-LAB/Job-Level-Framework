#ifndef JL_BASEMOVE_H
#define JL_BASEMOVE_H

#include <string>

namespace joblevel
{
/*!
	@brief	Base move is used to decouple with node, since each game has their 
			rules of move, lile Go use one piece to move but Connect6 use two, 
			some games need to select a piece to move, some games have additional
			action after make a move.
	@author	chaochin
	@date	2015/7/22
 */
class BaseMove
{
public:
	// forward declaration of BaseMove::Parser, need to declare below
	class Parser;

	typedef BaseMove* BaseMovePtr;

public:

	virtual ~BaseMove() {};
	virtual std::string serialize(std::string sSeperator = "", bool bUpperCase = true) const = 0;
	virtual bool isNullMove() const = 0;
	virtual bool isSameMove(BaseMovePtr pMove) const = 0;

protected:
	BaseMove() {}
	BaseMove(const BaseMove&);
	BaseMove& operator=(const BaseMove&);
};

typedef BaseMove* BaseMovePtr;

// forward declaration for NodePtr
class Node;
typedef Node* NodePtr;

/*!
	@brief	Parser interface of base move, for each game to implement their move 
			parser.
	@author	chaochin
	@date	2015/7/23
 */
class BaseMove::Parser
{
public:
	virtual std::string retrieveMove(const std::string& sInput) const = 0;
	virtual BaseMovePtr parseMove(const std::string& sInput) const = 0;
	virtual NodePtr expandPath(NodePtr pNode, const std::string& sPath) const = 0;
};

}

#endif
