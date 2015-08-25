#ifndef JL_SPECIFICINTEGRATOR_H
#define JL_SPECIFICINTEGRATOR_H

#include <cassert>
#include "Integrator.h"

namespace joblevel {

template <typename _SpecificBfsRetriever, typename _SpecificGameParser>
class SpecificIntegrator
	: public Integrator
{
public:
	virtual ~SpecificIntegrator() {};
	virtual BfsRetriever* makeRetriever(GameParser* pGameParser) const
	{
		_SpecificGameParser* pSpecificGameParser = dynamic_cast<_SpecificGameParser*>(pGameParser);
		assert(pSpecificGameParser != nullptr);
		return new _SpecificBfsRetriever(pSpecificGameParser);
	}
};

} // joblevel

#endif // JL_SPECIFICINTEGRATOR_H
