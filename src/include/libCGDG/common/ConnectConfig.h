#ifndef CONNECTCONFIG_H
#define CONNECTCONFIG_H

#include <vector>
#include <utility>
#include <string>

namespace cgdg
{
	namespace common
	{

class ConnectConfig
{
public:
	ConnectConfig();

	bool isStepConnectionEnabled() const;
	bool isReconnectionEnabled() const;
	const std::vector<std::pair<std::string, unsigned short> >& getConnectTargets() const;
	std::vector<std::pair<std::string, unsigned short> >& getConnectTargets();

	void enableStepConnection();
	void disableStepConnection();
	void enableReconnection();
	void disableReconnection();
	void addConnectTarget(const std::string& host, unsigned port);
private:
	bool m_bIsStepConnectionEnabled;
	bool m_bIsReconnectionEnabled;
	std::vector<std::pair<std::string, unsigned short> > m_connectTargets;
};

inline ConnectConfig::ConnectConfig()
: m_bIsStepConnectionEnabled(true), m_bIsReconnectionEnabled(true)
{
}

inline bool ConnectConfig::isStepConnectionEnabled() const
{
	return m_bIsStepConnectionEnabled;
}

inline bool ConnectConfig::isReconnectionEnabled() const
{
	return m_bIsReconnectionEnabled;
}

inline const std::vector<std::pair<std::string, unsigned short> >& ConnectConfig::getConnectTargets() const
{
	return const_cast<ConnectConfig*>(this)->getConnectTargets();
}

inline std::vector<std::pair<std::string, unsigned short> >& ConnectConfig::getConnectTargets()
{
	return m_connectTargets;
}

inline void ConnectConfig::enableStepConnection()
{
	m_bIsStepConnectionEnabled = true;
}

inline void ConnectConfig::disableStepConnection()
{
	m_bIsStepConnectionEnabled = false;
}

inline void ConnectConfig::enableReconnection()
{
	m_bIsReconnectionEnabled = true;
}

inline void ConnectConfig::disableReconnection()
{
	m_bIsReconnectionEnabled = false;
}

inline void ConnectConfig::addConnectTarget(const std::string& host, unsigned port)
{
	m_connectTargets.push_back(std::make_pair(host, port));
}

	}
}

#endif
