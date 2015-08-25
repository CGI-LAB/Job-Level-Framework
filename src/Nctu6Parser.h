#ifndef JL_NCTU6PARSER_H
#define JL_NCTU6PARSER_H

#include <map>
#include "GameParser.h"
#include "Connect6Move.h"

namespace joblevel 
{

class Nctu6Parser
	: public GameParser
{
public:
	Nctu6Parser(const std::string& sResult);
	virtual ~Nctu6Parser() {}
	GoMove::PlayerColor getColor() const;
	BaseMovePtr getMove() const;
	std::string getGameStatus() const;
};

} // joblevel

#endif //JL_CONNECT6JMSGPARSER_H
