#pragma once
#include <iostream>
#include <unordered_map>
#include <filesystem>

/* todo -> move settings & log into core lib */

typedef struct Settings
{
	uint32_t dwId = 1000;
	std::string PlayerNameString = "test";
	uint16_t sWindowHeight = 1920;
	uint16_t sWindowWidth = 1080;
	uint16_t bSound = 0;
}TSettings;

class CSettingsModule
{
public:
	CSettingsModule() = default;
	~CSettingsModule() = default;

	std::filesystem::path GetFilePath(const char* pszFilePath);
	inline const std::string& GetFileName() const { return m_loadedFile; }

	void LoadData();
	void InsertData();
	bool CheckIsEmptyFile();
	void ProccessData();
private:
	std::unordered_map<uint16_t, TSettings> m_settingsMap;
	TSettings m_pSettings;

	const char* m_loadedFile = "settings.dat";
};