#include "GoMove.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include "Node.h"

namespace joblevel
{

GoMovePtr GoMove::AllocMove(GoMove::PlayerColor color, Point point)
{
	GoMovePtr pGoMove = new GoMove(color, point);
	return pGoMove;
}

GoMove::GoMove(PlayerColor color, Point point)
	: m_color(color),
	  m_point(point)
{
}

GoMove::~GoMove()
{
	//std::cout << "Destruct GoMove " << serializeMove() << std::endl;
}

GoMove::PlayerColor GoMove::getColor() const
{
	return m_color;
}

Point GoMove::getPoint() const
{
	return m_point;
}

bool GoMove::isBlack() const
{
	return m_color == PLAYER_BLACK;
}

std::string GoMove::serialize(std::string sSeperator, bool bUpperCase) const
{
	std::ostringstream oss;
	oss << sSeperator << (getColor() == PLAYER_BLACK ? "B" : "W")
		<< "[" << serializePoint(bUpperCase, getPoint()) << "]";
	return oss.str();
}

std::string GoMove::serializePoint(bool bUpperCase, const Point& point) const
{
	if (point == Point::NULL_POINT)
		return "";
	char cStartChar = bUpperCase?'A':'a';
	std::string sPoint;
	sPoint += static_cast<char>(cStartChar + point.x());
	sPoint += static_cast<char>(cStartChar + point.y());
	return sPoint;
}

bool GoMove::isNullMove() const
{
	return m_point == Point::NULL_POINT;
}

bool GoMove::isSameMove(BaseMovePtr pMove) const
{
	GoMovePtr pGoMove = dynamic_cast<GoMove*>(pMove);
	return m_point == pGoMove->getPoint() && m_color == pGoMove->getColor();
}

std::string GoMove::Parser::retrieveMove(const std::string& sInput) const
{
	int n = sInput.find(";B[");
	if (n == std::string::npos) {
		n = sInput.find(";W[");
		if (n == std::string::npos)
			return "";
	}
	return sInput.substr(n, 6);
}

BaseMovePtr GoMove::Parser::parseMove(const std::string& sInput) const
{
	assert(sInput.length() == 6);
	GoMove::PlayerColor color = (sInput[1] == 'B')?PLAYER_BLACK:PLAYER_WHITE;
	Point point(static_cast<int>(sInput[3] - 'A'),
				static_cast<int>(sInput[4] - 'A'));
	GoMovePtr pGoMove = AllocMove(color, point);
	return pGoMove;
}

NodePtr GoMove::Parser::expandPath(NodePtr pNode, const std::string& sPath) const
{
	std::string sRestPath = sPath;
	NodePtr pNewNode = pNode;
	while (sRestPath.length() > 0) {
		std::string sMove = retrieveMove(sRestPath);
		if (sMove.length() == 0)
			return pNode;
		BaseMovePtr pMove = parseMove(sMove);
		if (pMove == nullptr)
			return pNode;
		if (pNewNode->isRoot() || pMove->isSameMove(pNewNode->getMove()) == false)
			pNewNode = pNewNode->generateChild(pMove);
		else if (pMove->isSameMove(pNewNode->getMove()))
			delete pMove;
		if (sRestPath.length() >= sMove.length()) {
			int n = sRestPath.find(sMove);
			sRestPath = sRestPath.substr(n + sMove.length());
		}
		if (sRestPath.length() < sMove.length())
			break;
	}
	return pNewNode;
}

}
