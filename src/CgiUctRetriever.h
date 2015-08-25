#ifndef JL_CGIUCTRETRIEVER_H
#define JL_CGIUCTRETRIEVER_H

#include "UctRetriever.h"

namespace joblevel
{

class CgiParser;

class CgiUctRetriever
	: public UctRetriever
{
public:
	CgiUctRetriever(CgiParser* pCgiParser);
	virtual ~CgiUctRetriever() {}
	virtual BfsData::WinningStatus getWinningStatus() const;
	virtual bool getStopExpanding() const;
	virtual double getWinRate() const;

private:
	CgiParser* m_pCgiParser;
};

}

#endif // JL_CGIUCTRETRIEVER_H
