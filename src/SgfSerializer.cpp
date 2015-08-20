#include "SgfSerializer.h"
#include "sstream"

namespace joblevel
{

std::string SgfSerializer::serialize()
{
	std::ostringstream oss;
	NodePtr pRoot = Node::GetRoot();
	oss << "(;"
		<< "C[" << replaceComment(pRoot->getComment()) << "]"
		<< serializeTree(pRoot)
		<< ")" << "C[" << replaceComment(pRoot->getComment()) << "]" // for Editor
		<< std::endl;
	return oss.str();
}

std::string SgfSerializer::serializeTree(NodePtr pNode)
{
	if (pNode->getChildrenSize() == 0)
		return "";
	
	std::ostringstream oss;
	bool hasMoreSiblings = pNode->getChildrenSize() > 1;
	NodePtr pChildSibling = pNode->getChild(0);
	for (; pChildSibling != nullptr; pChildSibling = pChildSibling->getRight()) {		
		if (hasMoreSiblings)
			oss << std::endl << "(";

		oss << pChildSibling->getMove()->serialize(";")
			<< "C[" << replaceComment(pChildSibling->getComment()) << "]";

		const Node::DataMap& dataMap = pChildSibling->getDataMap();
		for (Node::DataMap::const_iterator it = dataMap.begin(); it != dataMap.end(); ++it)
			oss << it->second->serialize();

		oss << serializeTree(pChildSibling);
		
		if (hasMoreSiblings)
			oss << ")";
	}
	return oss.str();
}

std::string SgfSerializer::replaceComment(const std::string& sComment)
{
	std::string sNewComment = sComment;
	sNewComment = replaceAll(sNewComment, "\\", "\\\\");
	sNewComment = replaceAll(sNewComment, "]", "\\]");
	sNewComment = replaceAll(sNewComment, ":", "\\:");
	return sNewComment;
}

std::string SgfSerializer::replaceAll(const std::string& sOrigin, const std::string& sFind,
	const std::string& sReplace)
{
	std::string sResult = sOrigin;
	std::string::size_type nFind = 0;
	while ((nFind = sResult.find(sFind, nFind)) != std::string::npos) {
		sResult.replace(nFind, sFind.length(), sReplace);
		nFind += sReplace.length();
	}
	return sResult;
}

}
