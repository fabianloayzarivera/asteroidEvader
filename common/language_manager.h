#pragma once
#include "globals.h"
#include <fstream>
#include <string>
#include "./rapidjson/document.h"
using namespace rapidjson;

enum LanguageId { LANGUAGE_ES, LANGUAGE_EN };


class LanguageManager {
private:
	LanguageId currentLanguage;
	Document   language;
public:
	LanguageManager();
	void		loadLanguage(LanguageId id);
	const char* getString(const char* key);
	LanguageId  getCurrentLanguage() { return currentLanguage; }
	
};