#ifndef JL_CGIPARSER_H
#define JL_CGIPARSER_H

#include "GameParser.h"

namespace joblevel
{

class CgiParser
	: public GameParser
{
public:
	CgiParser(const std::string& sResult);
	virtual ~CgiParser() {}
	virtual BaseMovePtr getMove() const;
	std::string getColor() const;
	int getCWin() const;
	bool getLast() const;
	double getWinRate() const;
};

}

#endif
