#include <fstream>
#include "SettingsModule.h"
#include "Log.h"

void CSettingsModule::LoadData()
{
	std::ifstream settingsFile(m_loadedFile);

	if (CheckIsEmptyFile())
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "FileManager::LoadData : Loaded data file is empty.\n");
		return;
	}

	if (!settingsFile)
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "FileManager::LoadData : File does not exist in a specified path.\nSpecify path or create requested file.\n");
		return;
	}

	while (!settingsFile.eof())
	{
		if (settingsFile >> m_pSettings.dwId >> m_pSettings.PlayerNameString >> m_pSettings.sWindowHeight >> m_pSettings.sWindowWidth >> m_pSettings.bSound)
			m_settingsMap.insert(std::make_pair(m_pSettings.dwId, m_pSettings));
		else
		{
			Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "FileManager::LoadData : Error reading data from file\n", m_loadedFile);
			break;
		}
		settingsFile.close();
	}

	if (m_settingsMap.empty())
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_ERROR, "FileManager::LoadData : No data loaded from file.\n");
		return;
	}

	/* retrieve data from unordered_map to check if it loaded correctly */
	for (const auto& pair : m_settingsMap)
	{
		Log::Instance().TraceLog(eLogType::LOG_TYPE_LOG, "Loaded - Id: %d, Name: %s, Height %d, Width %d, Sound %d, Score %d\n", pair.second.dwId, pair.second.PlayerNameString.c_str(), pair.second.sWindowHeight, pair.second.sWindowHeight, pair.second.bSound);
	}
}

void CSettingsModule::InsertData()
{
	/* insert file name set in SetFileName if file does not exist create it */
	std::ofstream settingsFile(m_loadedFile);

	while (settingsFile.is_open())
	{
		settingsFile << m_pSettings.dwId << "	" << m_pSettings.PlayerNameString << "	" <<  m_pSettings.sWindowHeight << "	" << m_pSettings.sWindowWidth << "	" << m_pSettings.bSound;
		settingsFile.close();
	}
}

std::filesystem::path CSettingsModule::GetFilePath(const char* pszFilePath)
{
	return std::filesystem::weakly_canonical(std::filesystem::path(pszFilePath)).parent_path();
}

bool CSettingsModule::CheckIsEmptyFile()
{
	std::filesystem::path filePath = GetFilePath(m_loadedFile);
	std::error_code ec;
	uintmax_t fileSize = std::filesystem::file_size(filePath, ec);

	if (ec)
	{
		return true;
	}

	return (fileSize == 0); // Return true if file size is 0, false otherwise
}

void CSettingsModule::ProccessData()
{
	if (CheckIsEmptyFile())
		InsertData();
	else
		LoadData();
}