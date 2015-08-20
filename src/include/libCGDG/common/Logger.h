#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <cassert>
#include <locale>
#include <algorithm>

namespace cgdg
{
	namespace common
	{

class Logger
{
public:
	static Logger& getInstance();

	void setLevel(int iLevel);
	void log(int iLevel, const std::string& catagory, std::string content);

	void openNullStream();
	void open(const std::string& fileName);
private:
	Logger();
	static Logger g_loggerInstance;

	static void eraseControlCharacter(std::string& sentence);
	static std::string getCurrentDateAndTime(); // Locale dependent by using <locale>.

	int m_iLevel;
	std::ofstream m_logStream;

};

inline Logger& Logger::getInstance()
{
	return g_loggerInstance;
}

inline Logger::Logger()
: m_iLevel(1)
{
	openNullStream();
}

inline void Logger::setLevel(int iLevel)
{
	m_iLevel = iLevel;
}

inline void Logger::open(const std::string& fileName)
{
	if (m_logStream.is_open()) m_logStream.close();
	m_logStream.open(fileName.c_str());
	if (m_logStream.fail()) openNullStream();
}

inline void Logger::eraseControlCharacter(std::string& sentence)
{
	std::string::iterator last = std::remove_if(sentence.begin(), sentence.end(), iscntrl);
	sentence.erase(last, sentence.end());
}

	}
}

#endif
