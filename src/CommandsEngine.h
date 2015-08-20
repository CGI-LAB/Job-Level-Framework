#ifndef JL_COMMANDSENGINE_H
#define JL_COMMANDSENGINE_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <boost/shared_ptr.hpp>

namespace joblevel
{

class CommandsEngine
{
private:
	struct Func
	{
		virtual void operator()() = 0;
	};

	typedef boost::shared_ptr<Func> FuncPtr;

	template<typename _T, typename _F>
	struct FuncInherit : public Func
	{
		_T* m_instance;
		_F m_fp;
		FuncInherit(_T* instance, _F fp)
			: m_instance(instance), m_fp(fp) {}
		virtual ~FuncInherit() {}
		void operator()() { (*m_instance.*m_fp)(); }
	};

	class Entry
	{
	public:
		Entry() {}
		Entry(std::string key, FuncPtr fp, size_t nMinArgc = 0, size_t nMaxArgc = 0);
		size_t getMinArgc() const;
		size_t getMaxArgc() const;
		const std::string& getKey() const;
		FuncPtr getFunction() const;
		bool operator<(const Entry& rhs) const;
	private:
		std::string m_key;
		FuncPtr m_fp;
		size_t m_nMinArgc;
		size_t m_nMaxArgc;
	};

public:
	CommandsEngine(std::ostream& os);
	void runCommand(const std::string& sCommandLine);
	bool hasQuit() const;
	std::vector<std::string> getCompleters();

	template<typename _T, typename _Function>
	void registerFunction(const std::string& sCommand, _T* instancem, _Function fp,
		int nMinArgc, int nMaxArgc = -1);
	void unregister(const std::string sCommand);
	std::vector<std::string>& getArgs();

protected:
	void cmdListCommands();
	void cmdKnownCommand();
	void cmdDefault();
	void cmdQuit();

private:
	CommandsEngine(const CommandsEngine&);
	CommandsEngine& operator=(const CommandsEngine&);

	bool checkArgSize(const Entry* pEntry);

private:
	std::map<std::string, Entry> m_mapFunction;
	std::ostream& m_os;

protected:
	std::string m_sCommand;
	std::vector<std::string> m_vArgs;
	std::string m_sCommandLine;

	bool m_isQuit;
};

template<typename _T, typename _Function>
void CommandsEngine::registerFunction(const std::string& sCommand, _T* instance,
	_Function fp, int nMinArgc, int nMaxArgc)
{
	if (nMaxArgc < nMinArgc) nMaxArgc = nMinArgc;
	FuncPtr pFunc(new FuncInherit<_T, _Function>(instance, fp)); 
	m_mapFunction[sCommand] = Entry(sCommand, pFunc, nMinArgc, nMaxArgc);
}

}

#endif
