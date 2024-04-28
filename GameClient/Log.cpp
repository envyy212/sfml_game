#include <cstdarg>
#include "Log.h"

int Log::TraceLog(eLogType logType, const char* pszLogMsg, ...)
{
	va_list arg;
	int done;

	if (!pszLogMsg)
	{
		std::cout << "pszLogMsg is null" << std::endl;
		return -1;
	}

	for (auto it = m_logLvToStringMap.begin(); it != m_logLvToStringMap.end(); it++)
	{
		if (it->first == static_cast<int>(logType))
		{
			std::string logMessage;
			logMessage.append(it->second);
			logMessage.append(pszLogMsg);

			va_start(arg, pszLogMsg);

			int len = _vscprintf(logMessage.c_str(), arg) + 1;
			std::vector<char> formattedMsg(len);
			vsnprintf(formattedMsg.data(), len, logMessage.c_str(), arg);

			done = fprintf(stdout, "%s", formattedMsg.data());
			va_end(arg);
		}
	}

	return 0;
}