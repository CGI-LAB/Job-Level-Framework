#ifndef JL_INTEGRATOR_H
#define JL_INTEGRATOR_H

#include "GameParser.h"
#include "BfsRetriever.h"

namespace joblevel {

class Integrator
{
public:
	virtual ~Integrator() {};
	virtual BfsRetriever* makeRetriever(GameParser* pGameParser) const = 0;
};

} // joblevel

#endif // JL_INTEGRATOR_H
