#ifndef JL_SGFSERIALIZER_H
#define JL_SGFSERIALIZER_H

#include "Node.h"
#include <string>

namespace joblevel
{

class SgfSerializer
{
public:
	std::string serialize();

private:
	std::string serializeTree(NodePtr pNode);
	std::string replaceComment(const std::string& sComment);
	std::string replaceAll(const std::string& sOrigin, 
						   const std::string& sFind,
						   const std::string& sReplace);

};

}

#endif
