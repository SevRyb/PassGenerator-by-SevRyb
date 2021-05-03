#include "ConfigManager.h"

const string APP_TAG_VERSION = "** V1.0 [2021.05.03] - PassGenerator by SevRyb **";

StartUpConfig::StartUpConfig()
{
}

bool StartUpConfig::LoadSettings()
{
    // Reading Config File
	std::ifstream file_r("config/startup.conf");
	if (!file_r)
	{
		return false;
	}
    string token;
    string lineData;
    while (!file_r.eof())
    {
        getline(file_r, lineData);
        stringstream sStream(lineData);
        sStream >> token;
        
        if (token == "UI_win_width")
        {
            sStream >> m_Startup_Config.UI_win_width;
        }
        else if (token == "UI_win_height")
        {
            sStream >> m_Startup_Config.UI_win_height;
        }
        else if (token == "UI_CHECKED_checkbox_letters")
        {
            sStream >> m_Startup_Config.UI_CHECKED_checkbox_letters;
        }
        else if (token == "UI_CHECKED_checkbox_digits")
        {
            sStream >> m_Startup_Config.UI_CHECKED_checkbox_digits;
        }
        else if (token == "UI_CHECKED_checkbox_other_symbols")
        {
            sStream >> m_Startup_Config.UI_CHECKED_checkbox_other_symbols;
        }
        else if (token == "UI_CHECKED_checkbox_custom_symbols")
        {
            sStream >> m_Startup_Config.UI_CHECKED_checkbox_custom_symbols;
        }
        else if (token == "UI_CHECKED_checkbox_exclude_symbols")
        {
            sStream >> m_Startup_Config.UI_CHECKED_checkbox_exclude_symbols;
        }
        else if (token == "UI_case")
        {
            sStream >> m_Startup_Config.UI_case;
        }
        else if (token == "UI_custom_symbols")
        {
            sStream >> m_Startup_Config.UI_custom_symbols;
        }
        else if (token == "UI_exclude_symbols")
        {
            sStream >> m_Startup_Config.UI_exclude_symbols;
        }
        else if (token == "UI_pass_length")
        {
            sStream >> m_Startup_Config.UI_pass_length;
        }
        else if (token == "UI_previous_pass")
        {
            sStream >> m_Startup_Config.UI_previous_pass;
        }
    }
	file_r.close();

	return true;
}

Startup_Config* StartUpConfig::GetSettings()
{
	return &m_Startup_Config;
}

bool StartUpConfig::SaveSettings()
{
    // Writing config file

    if (CreateDirectoryA(m_config_folder.c_str(), NULL) ||
        ERROR_ALREADY_EXISTS == GetLastError())
    {
        std::ofstream file_w("config/startup.conf");
        if (!file_w)
        {
            return false;
        }
        file_w << APP_TAG_VERSION << "\n";
        file_w << "UI_win_width " << m_Startup_Config.UI_win_width << "\n";
        file_w << "UI_win_height " << m_Startup_Config.UI_win_height << "\n";
        file_w << "UI_CHECKED_checkbox_letters " << m_Startup_Config.UI_CHECKED_checkbox_letters << "\n";
        file_w << "UI_CHECKED_checkbox_digits " << m_Startup_Config.UI_CHECKED_checkbox_digits << "\n";
        file_w << "UI_CHECKED_checkbox_other_symbols " << m_Startup_Config.UI_CHECKED_checkbox_other_symbols << "\n";
        file_w << "UI_CHECKED_checkbox_custom_symbols " << m_Startup_Config.UI_CHECKED_checkbox_custom_symbols << "\n";
        file_w << "UI_CHECKED_checkbox_exclude_symbols " << m_Startup_Config.UI_CHECKED_checkbox_exclude_symbols << "\n";
        file_w << "UI_case " << m_Startup_Config.UI_case << "\n";
        file_w << "UI_custom_symbols " << m_Startup_Config.UI_custom_symbols << "\n";
        file_w << "UI_exclude_symbols " << m_Startup_Config.UI_exclude_symbols << "\n";
        file_w << "UI_pass_length " << m_Startup_Config.UI_pass_length << "\n";
        file_w << "UI_previous_pass " << m_Startup_Config.UI_previous_pass;
        file_w.close();
    }
    else
    {
        return false;
    }
    
	return true;
}