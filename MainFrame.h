#pragma once
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "PassGenerator.h"
#include "ConfigManager.h"
#include "Defines.h"

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
	
	void OnInit(int* l_win_width, int* l_win_height);
private:
	void OnExit(wxCloseEvent& event);
	void Generate_btn(wxCommandEvent& event);

	StartUpConfig m_StartUpConfig;
	Startup_Config* m_Startup_Config;

	PassGenerator m_PassGenerator;
	string* m_generated_pass;

	string m_cases[3] = 
	{
		"Mixed case", 
		"Upper case", 
		"Lower case"
	};

	string m_case;

	enum caseSettings m_caseSettings;

	bool m_useDigits;
	bool m_useOtherSymbols;
	bool m_useCustomSymbols;
	string m_customSymbols;
	bool m_useEcludeSymbols;
	string m_excludeSymbols;
	int m_passLength = 0;

	wxFont font_button;
	wxFont font_checkbox;
	wxFont font_label_normal;

	wxPanel* panel_top;
	wxPanel* panel_bottom_buttons;

	wxBoxSizer* sizer_v_bottom;
	wxBoxSizer* sizer_h_letters;
	wxBoxSizer* sizer_h_other_symbols;
	wxBoxSizer* sizer_h_custom_symbols;
	wxBoxSizer* sizer_h_exclude_symbols;
	wxBoxSizer* sizer_h_pass_leght;
	wxStaticBoxSizer* sizer_v_charset;

	wxCheckBox* checkbox_letters;
	wxCheckBox* checkbox_digits;
	wxCheckBox* checkbox_other_symbols;
	wxCheckBox* checkbox_custom_symbols;
	wxCheckBox* checkbox_exclude_symbols;

	wxButton* button_generate;

	wxTextCtrl* textctrl_other_symbols;
	wxTextCtrl* textctrl_custom_symbols;
	wxTextCtrl* textctrl_exclude_symbols;
	wxTextCtrl* textctrl_result;

	wxStaticText* statictext_pass_leght;

	wxComboBox* combobox_letter_case;
	wxSpinCtrl* spinctrl_pass_leght;

	DECLARE_EVENT_TABLE()
};