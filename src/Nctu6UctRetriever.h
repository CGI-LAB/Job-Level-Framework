#ifndef JL_NCTU6UCTRETRIEVER_H
#define JL_NCTU6UCTRETRIEVER_H

#include <map>
#include "UctRetriever.h"

namespace joblevel
{

class Nctu6Parser;

class Nctu6UctRetriever
	: public UctRetriever
{
public:
	Nctu6UctRetriever(Nctu6Parser* pNctu6Parser);
	virtual ~Nctu6UctRetriever() {}
	virtual BfsData::WinningStatus getWinningStatus() const;
	virtual bool getStopExpanding() const;
	virtual double getWinRate() const;
	
private:
	void initializeWinRateTable();

private:
	Nctu6Parser* m_pNctu6Parser;
	mutable std::map<std::string, double> m_winRateTable;
};

}

#endif // JL_NCTU6UCTRETRIEVER_H
