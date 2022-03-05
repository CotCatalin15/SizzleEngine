#include "../Public/SLogContext.h"
#include <memory>


SLogContext::SLogContext() 
{
	

}

SLogContext::~SLogContext()
{
}

bool SLogContext::Init()
{
	_logFile.open("Log.txt", std::ios_base::app);
	if (_logFile.fail())
		return false;
	return true;
}

void SLogContext::Destroy()
{
	_logFile.close();
}

void SLogContext::LogMessage(std::string const& LogName, std::string const& Message, LogVerbosity Verbosity)
{
	_logFile << '[' << LogName << ']' << "\tMessage: " << Message << '\n';

	switch (Verbosity)
	{
	case LogVerbosity::Log:
		break;
	case LogVerbosity::Warning:
		break;
	case LogVerbosity::Error:
		exit(-1);
		break;
	default:
		break;
	}

}

SLogContext* SLogContext::Get()
{
	static std::unique_ptr<SLogContext> context = std::make_unique<SLogContext>();
	return context->Get();
}
