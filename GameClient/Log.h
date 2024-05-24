#pragma once
#include "../TheCore/pch.h"

#include <iostream>

enum class eLogType
{
	LOG_TYPE_LOG,
	LOG_TYPE_WARNING,
	LOG_TYPE_ERROR,
	LOG_TYPE_MAX_NUM
};

class Log
{
public:
	Log(const Log&) = delete;

	static Log& Instance()
	{
		static Log s_Instance;
		return s_Instance;
	}

	inline uint8_t GetLogLevel() const { return m_logLevel; }
	inline void SetLogLevel(uint8_t logLevel) { m_logLevel = logLevel; }

	/*
	TraceLog LogyTypes
		LOG_TYPE_LOG, - 1
		LOG_TYPE_WARNING,- 2
		LOG_TYPE_ERROR,- 3
		LOG_TYPE_MAX_NUM - 4
	*/
	int TraceLog(eLogType logType, const char* format, ...);

private:
	uint8_t m_logLevel;
	std::unordered_map<uint8_t, std::string> m_logLvToStringMap;

	Log() : m_logLvToStringMap(
		{
			{0, "<Log> :"},
			{1, "<Warning> :"},
			{2, "<Error> :"}
		}
	), m_logLevel(0) {};

	~Log()
	{
		m_logLvToStringMap.clear();
	}
};