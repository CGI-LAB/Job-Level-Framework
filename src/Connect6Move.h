#ifndef JL_CONNECT6MOVE_H
#define JL_CONNECT6MOVE_H

#include "GoMove.h"

namespace joblevel
{

class Connect6Move : public GoMove
{
public:
	// forward declaration of Connect6Move::Parser, need to declare below
	class Parser;

	typedef Connect6Move* Connect6MovePtr;
	static Connect6MovePtr AllocMove(GoMove::PlayerColor color, Point point, Point point2);

public:
	virtual ~Connect6Move();
	Point getPoint2() const;
	virtual std::string serialize(std::string sSeperator = "", bool bUpperCase = true) const;
	virtual bool isNullMove() const;
	virtual bool isSameMove(BaseMovePtr pMove) const;

protected:
	Connect6Move(GoMove::PlayerColor color, Point point, Point point2);
	Connect6Move(const Connect6Move&);
	Connect6Move& operator=(const Connect6Move&);

private:
	Point m_point2;
};

typedef Connect6Move* Connect6MovePtr;

class Connect6Move::Parser : public GoMove::Parser
{
public:
	virtual std::string retrieveMove(const std::string& sInput) const;
	virtual BaseMovePtr parseMove(const std::string& sInput) const;
};

}

#endif
