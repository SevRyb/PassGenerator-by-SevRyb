#pragma once
#include "Defines.h"
#include <set>
#include <ctime>

class PassGenerator
{
public:
	PassGenerator();

	string* GeneratePass(
		unsigned int l_case, 
		bool l_useDigits, 
		bool l_useOtherSymbols,
		string l_customSymbols,
		string l_excludeSymbols,
		int l_passLength
	);

	const string* GetOtherSymbols();

private:
	const string m_alphabetSymbolsLower_en = 
		"abcdefghijklmnopqrstuvwxyz";
	const string m_alphabetSymbolsUpper_en = 
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const string m_alphabetDigits = "0123456789";
	const string m_otherSymbols = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~";

	string m_currentSymbols;
	string m_currentSymbolsBuffer;
	string m_currentSymbolsClean;
	char m_symbol_exclude;
	int m_random_index;
	string m_generatedPass;
};