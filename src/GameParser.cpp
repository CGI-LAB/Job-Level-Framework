#include "GameParser.h"

namespace joblevel
{

GameParser::GameParser(const std::string& sResult) : m_sResult(sResult) 
{
}

std::string GameParser::getStringFromResult(const std::string& sTag) const
{
	// get position after sTag and a '['
	size_t iPos = m_sResult.find(sTag + "[") + sTag.length() + 1;
	std::string sTarget = m_sResult.substr(iPos);
	sTarget = sTarget.substr(0, sTarget.find(']'));
	return sTarget;
}

}
