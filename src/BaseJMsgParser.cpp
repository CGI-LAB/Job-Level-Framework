#include "BaseJMsgParser.h"

namespace joblevel
{

std::string BaseJMsgParser::getStringFromResult(const std::string& sTag, 
	const std::string& sResult) const
{
	// get position after sTag and a '['
	size_t iPos = sResult.find(sTag + "[") + sTag.length() + 1;
	std::string sTarget = sResult.substr(iPos);
	sTarget = sTarget.substr(0, sTarget.find(']'));
	return sTarget;
}

}
