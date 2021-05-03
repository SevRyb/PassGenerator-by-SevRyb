#include "PassGenerator.h"

PassGenerator::PassGenerator()
{
	srand(time(NULL));
}

const string* PassGenerator::GetOtherSymbols() 
{ 
	return &m_otherSymbols; 
}

string* PassGenerator::GeneratePass(
	unsigned int l_case,
	bool l_useDigits,
	bool l_useOtherSymbols,
	string l_customSymbols,
	string l_excludeSymbols,
	int l_passLength
)
{
	if (l_case != 0)
	{
		if(l_case == mixedCase)
		{
			m_currentSymbols += m_alphabetSymbolsLower_en;
			m_currentSymbols += m_alphabetSymbolsUpper_en;
		}
		if(l_case == upperCase)
		{
			m_currentSymbols += m_alphabetSymbolsUpper_en;
		}
		if(l_case == lowerCase)
		{
			m_currentSymbols += m_alphabetSymbolsLower_en;
		}
	}

	if (l_useDigits)
	{
		m_currentSymbols += m_alphabetDigits;
	}

	if (l_useOtherSymbols)
	{
		m_currentSymbols += m_otherSymbols;
	}

	if (l_customSymbols.length() > 0)
	{
		l_customSymbols.erase(
			remove(l_customSymbols.begin(), l_customSymbols.end(), ' '),
			l_customSymbols.end()
		);

		m_currentSymbols += l_customSymbols;

		std::set<char> chars;

		m_currentSymbols.erase(
			std::remove_if(
				m_currentSymbols.begin(),
				m_currentSymbols.end(),
				[&chars](char i) {
					// If encountered character, remove this one.
					if (chars.count(i)) { return true; }

					// Otherwise, mark this character encountered and don't remove.
					chars.insert(i);
					return false;
				}
			),
			m_currentSymbols.end()
					);
	}

	
	if (l_excludeSymbols.length() > 0)
	{
		for (size_t index = 0; index < l_excludeSymbols.size(); index++)
		{
			m_symbol_exclude = l_excludeSymbols[index];
			m_currentSymbols.erase(
				remove(m_currentSymbols.begin(), m_currentSymbols.end(), m_symbol_exclude), 
				m_currentSymbols.end()
			);
		}
	}

	m_currentSymbolsClean = m_currentSymbols;
	m_currentSymbols = "";

	if (m_currentSymbolsClean != "")
	{
		for (size_t i = 0; i < l_passLength; i++)
		{
			
			m_random_index = rand() % (m_currentSymbolsClean.size());
			m_generatedPass += m_currentSymbolsClean[m_random_index];
		}
	}
	
	m_currentSymbolsClean = "";

	return &m_generatedPass;
}
