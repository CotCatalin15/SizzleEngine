#pragma once
#include <string>
#include <fstream>
#include "../../CoreAPI.h"

enum class LogVerbosity
{
	Log,
	Warning,
	Error
};

class CORE_API SLogContext
{
public:
	SLogContext();
	~SLogContext();

	bool Init();
	void Destroy();

	void LogMessage(std::string const& LogName, std::string const& Message, LogVerbosity Verbosity);


	static SLogContext* Get();
private:
	std::ofstream _logFile;
};
