#ifndef COMMANDDATA_H
#define COMMANDDATA_H

#include <string>
#include <vector>
#include <sstream>
#include <cassert>

class TiXmlNode;

namespace cgdg
{
	namespace common
	{

class CommandData
{
public:
	virtual void insertInto(TiXmlNode& parentNode) const = 0;	//for send command
	virtual int fetch(const TiXmlNode& parentNode) = 0;			//for receive command
	virtual ~CommandData();
protected:
	static void insert(TiXmlNode& parentNode, const std::string& elementName, const std::string& contentText);
	static void insert(TiXmlNode& parentNode, const std::string& elementName, int contentValue);
	static void insert(TiXmlNode& parentNode, const std::string& elementName, unsigned contentValue);
	static void insert(TiXmlNode& parentNode, const std::string& elementName, double contentValue);
	static void insert(TiXmlNode& parentNode, const std::string& elementName);
	template<typename T>
	static std::string translateToString(const std::vector<T>& data);
};

inline CommandData::~CommandData()
{
}

template<typename T>
std::string CommandData::translateToString(const std::vector<T>& data)
{
	std::stringstream bufferStream;
	assert(!data.empty());
	bufferStream << data[0];
	for (unsigned i = 1; i < data.size(); i++) {
		bufferStream << " " << data[i];
	}
	return bufferStream.str();
}

	}
}

#endif
