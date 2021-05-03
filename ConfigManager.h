#pragma once
#include "Defines.h"
#include <fstream>
#include <Windows.h>

struct Startup_Config
{
	int UI_win_width = 447;
	int UI_win_height = 579;
	bool UI_CHECKED_checkbox_letters = true;
	bool UI_CHECKED_checkbox_digits = true;
	bool UI_CHECKED_checkbox_other_symbols = false;
	bool UI_CHECKED_checkbox_custom_symbols = false;
	bool UI_CHECKED_checkbox_exclude_symbols = false;
	int UI_case = mixedCase;
	string UI_custom_symbols = "custom";
	string UI_exclude_symbols = "exclude";
	int UI_pass_length = 8;
	string UI_previous_pass = "YourBestPass";
};


class StartUpConfig
{
public:
	StartUpConfig();
	bool LoadSettings();
	Startup_Config* GetSettings();
	bool SaveSettings();
private:
	Startup_Config m_Startup_Config;
	const string m_config_folder = "config/";
};
