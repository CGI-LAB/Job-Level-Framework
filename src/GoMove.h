#ifndef JL_GOMOVE_H
#define JL_GOMOVE_H

#include <string>
#include "BaseMove.h"
#include "Point.h"

namespace joblevel
{

class GoMove : public BaseMove
{
public:
	// forward declaration of GoMove::Parser, need to declare below
	class Parser;

	enum PlayerColor
	{
		PLAYER_BLACK, PLAYER_WHITE
	};

	typedef GoMove* GoMovePtr;
	static GoMovePtr AllocMove(PlayerColor color, Point point);

public:
	virtual ~GoMove();
	PlayerColor getColor() const;
	Point getPoint() const;
	bool isBlack() const;
	virtual std::string serialize(std::string sSeperator = "", bool bUpperCase = true) const;
	virtual bool isNullMove() const;
	virtual bool isSameMove(BaseMovePtr pMove) const;

protected:
	GoMove(PlayerColor color, Point point);
	GoMove(const GoMove&);
	GoMove& operator=(const GoMove&);
	virtual std::string serializePoint(bool bUpperCase, const Point& point) const;

private:
	PlayerColor m_color;
	Point m_point;
};

typedef GoMove* GoMovePtr;

class GoMove::Parser : public BaseMove::Parser
{
public:
	virtual std::string retrieveMove(const std::string& sInput) const;
	virtual BaseMovePtr parseMove(const std::string& sInput) const;
	virtual NodePtr expandPath(NodePtr pNode, const std::string& sPath) const;
};

}

#endif