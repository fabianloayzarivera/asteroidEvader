#include "stdafx.h"
#include "language_manager.h"
#include <string>

LanguageManager::LanguageManager() 
{
	loadLanguage(LANGUAGE_EN);

}

void LanguageManager::loadLanguage(LanguageId id) 
{
	std::string filename;
	switch (id)
	{
	case LANGUAGE_ES:
		filename = "../data/ES.json";
		break;
	case LANGUAGE_EN:
		filename = "../data/EN.json";
		break;
	default:
		filename = "../data/EN.json";
		break;
	}

	std::ifstream ifs(filename);
	std::string content((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
	language.Parse(content.c_str());
	OutputDebugStringA(content.c_str());

	if (language.IsObject()) {
		OutputDebugStringA("Language Loaded!");
		currentLanguage = id;
	}
	else 
		OutputDebugStringA("Failed to load Language!");
	
}

const char* LanguageManager::getString(const char* key) 
{
	if (language.HasMember(key))
	{
		return language[key].GetString();
	}
	else 
	{	
		return "";
	}
}