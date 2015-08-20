#include "Connect6Move.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include "Node.h"

namespace joblevel
{

Connect6MovePtr Connect6Move::AllocMove(GoMove::PlayerColor color, 
	Point point, Point point2)
{
	Connect6MovePtr pMove = new Connect6Move(color, point, point2);
	return pMove;
}

Connect6Move::Connect6Move(GoMove::PlayerColor color,
	Point point, Point point2)
	: GoMove::GoMove(color, point < point2 ? point : point2),
	  m_point2(point < point2 ? point2 : point)
{
}

Connect6Move::~Connect6Move()
{
	//std::cout << "Destruct Connect6Move " << serializeMove() << std::endl;
}

Point Connect6Move::getPoint2() const
{
	return m_point2;
}

std::string Connect6Move::serialize(std::string sSeperator, bool bUpperCase) const
{
	std::ostringstream oss;
	oss << GoMove::serialize(sSeperator, bUpperCase)
		<< sSeperator << (getColor() == PLAYER_BLACK ? "B" : "W")
		<< "[" << serializePoint(bUpperCase, getPoint2()) << "]";
	return oss.str();
}

bool Connect6Move::isNullMove() const
{
	return m_point2 == Point::NULL_POINT && GoMove::isNullMove();
}

bool Connect6Move::isSameMove(BaseMovePtr pMove) const
{
	Connect6MovePtr pConnect6Move = dynamic_cast<Connect6Move*>(pMove);
	if (pConnect6Move == nullptr)
		return false;
	return m_point2 == pConnect6Move->getPoint2() && GoMove::isSameMove(pMove);;
}

std::string Connect6Move::Parser::retrieveMove(const std::string& sInput) const
{
	int nBlack = sInput.find(";B[");
	int nWhite = sInput.find(";W[");
	bool bRetriveBlackMove = true;
	// check witch to retrive
	if (nBlack == std::string::npos && nWhite == std::string::npos)
		return "";
	else if (nWhite == std::string::npos)
		bRetriveBlackMove = true;
	else if (nBlack == std::string::npos)
		bRetriveBlackMove = false;
	else
		bRetriveBlackMove = nBlack < nWhite;
	// chech one (for first move) or two move to retrive
	if (bRetriveBlackMove) {
		int nBlack2 = sInput.find(";B[", nBlack + 1);
		if (nBlack2 == std::string::npos || nBlack2 > nBlack + 6)
			return sInput.substr(nBlack, 6);
		return sInput.substr(nBlack, 12);
	} else {
		int nWhite2 = sInput.find(";W[", nWhite + 1);
		if (nWhite2 == std::string::npos || nWhite2 > nWhite + 6)
			return ""; // white piece will never be only one piece
		return sInput.substr(nWhite, 12);
	}
}

BaseMovePtr Connect6Move::Parser::parseMove(const std::string& sInput) const
{
	assert(sInput.length() == 6 || sInput.length() == 12);
	GoMove::PlayerColor color = (sInput[1] == 'B')?PLAYER_BLACK:PLAYER_WHITE;
	Point point(static_cast<int>(sInput[3] - 'A'),
				static_cast<int>(sInput[4] - 'A'));
	if (sInput.length() == 6) {
		GoMovePtr pGoMove = GoMove::AllocMove(color, point);
		return pGoMove;
	} else {
		Point point2(static_cast<int>(sInput[9] - 'A'),
					 static_cast<int>(sInput[10] - 'A'));
		Connect6MovePtr pConnect6Move = AllocMove(color, point, point2);
		return pConnect6Move;
	}
}

}
