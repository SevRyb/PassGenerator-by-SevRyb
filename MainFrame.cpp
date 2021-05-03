#include "MainFrame.h"

MainFrame::MainFrame(const wxString& title, const wxPoint& pos, const wxSize& size) 
	: wxFrame(nullptr, wxID_ANY, title, pos, size)
{}

void MainFrame::OnInit(int* l_win_width, int* l_win_height) {

	if (!m_StartUpConfig.LoadSettings()) 
	{
		//this->Destroy();
	};
	m_Startup_Config = m_StartUpConfig.GetSettings();

	*l_win_width = m_Startup_Config->UI_win_width;
	*l_win_height = m_Startup_Config->UI_win_height;

	wxFont my_font = wxFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
		false, "Arial");

	font_checkbox = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_EXTRALIGHT,
		false, "Arial");

	font_button = wxFont(25, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
		false, "Arial");

	font_label_normal = wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL,
		false, "Arial");
	

	checkbox_letters = new wxCheckBox(this, wxID_ANY, " Letters (A-Z)", wxDefaultPosition, wxDefaultSize);
	checkbox_letters->SetOwnForegroundColour(wxColor(68, 68, 68));
	combobox_letter_case = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, NULL, wxCB_READONLY);
	combobox_letter_case->SetForegroundColour(wxColor(68, 68, 68));
	//combobox_letter_case->SetExtraStyle(wxCB_READONLY);

	checkbox_letters->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
		if (checkbox_letters->IsChecked())
		{
			combobox_letter_case->Enable();
		}
		else
		{
			combobox_letter_case->Disable();
		}
		});
	
	checkbox_digits = new wxCheckBox(this, wxID_ANY, " Digits (0-9)", wxDefaultPosition, wxDefaultSize);
	checkbox_digits->SetOwnForegroundColour(wxColor(68, 68, 68));

	checkbox_other_symbols = new wxCheckBox(this, wxID_ANY, " Other symbols", wxDefaultPosition, wxDefaultSize);
	checkbox_other_symbols->SetOwnForegroundColour(wxColor(68, 68, 68));
	
	textctrl_other_symbols = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);
	textctrl_other_symbols->SetOwnForegroundColour(wxColor(68, 68, 68));
	textctrl_other_symbols->SetEditable(false);

	checkbox_other_symbols->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
		if (checkbox_other_symbols->IsChecked())
		{
			textctrl_other_symbols->Enable();
		}
		else
		{
			textctrl_other_symbols->Disable();
		}
		} );

	checkbox_custom_symbols = new wxCheckBox(this, wxID_ANY, " Custom symbols", wxDefaultPosition, wxDefaultSize);
	checkbox_custom_symbols->SetOwnForegroundColour(wxColor(68, 68, 68));
	textctrl_custom_symbols = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);
	textctrl_custom_symbols->SetOwnForegroundColour(wxColor(68, 68, 68));

	checkbox_custom_symbols->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
		if (checkbox_custom_symbols->IsChecked())
		{
			textctrl_custom_symbols->Enable();
		}
		else
		{
			textctrl_custom_symbols->Disable();
		}
		});
	
	checkbox_exclude_symbols = new wxCheckBox(this, wxID_ANY, " Exclude symbols", wxDefaultPosition, wxDefaultSize);
	checkbox_exclude_symbols->SetOwnForegroundColour(wxColor(68, 68, 68));
	textctrl_exclude_symbols = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);
	textctrl_exclude_symbols->SetOwnForegroundColour(wxColor(68, 68, 68));

	checkbox_exclude_symbols->Bind(wxEVT_CHECKBOX, [=](wxCommandEvent& event) {
		if (checkbox_exclude_symbols->IsChecked())
		{
			textctrl_exclude_symbols->Enable();
		}
		else
		{
			textctrl_exclude_symbols->Disable();
		}
		});

	statictext_pass_leght = new wxStaticText(this, wxID_ANY, "  Password length", wxDefaultPosition, wxDefaultSize);
	statictext_pass_leght->SetOwnForegroundColour(wxColor(68, 68, 68));
	spinctrl_pass_leght = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize);
	spinctrl_pass_leght->SetForegroundColour(wxColor(68, 68, 68));

	textctrl_result = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition);
	textctrl_result->SetForegroundColour(wxColor(179, 78, 233));

	button_generate = new wxButton(this, wxID_ANY, "Generate");
	button_generate->SetForegroundColour(wxColor(68, 68, 68));
	button_generate->Bind(wxEVT_BUTTON, &MainFrame::Generate_btn, this);
	button_generate->SetFocus();


	// Restoring Config
	if (m_Startup_Config->UI_CHECKED_checkbox_letters)
	{
		checkbox_letters->SetValue(true);
	}
	else
	{
		combobox_letter_case->Disable();
	}
	combobox_letter_case->Append("Mixed case");
	combobox_letter_case->Append("Upper case");
	combobox_letter_case->Append("Lower case");
	switch (m_Startup_Config->UI_case)
	{
	case notUseCase:
		checkbox_letters->SetValue(false);
		combobox_letter_case->SetValue("Mixed case");
		combobox_letter_case->Disable();
		break;
	case mixedCase:
		combobox_letter_case->SetValue("Mixed case");
		break;
	case upperCase:
		combobox_letter_case->SetValue("Upper case");
		break;
	case lowerCase:
		combobox_letter_case->SetValue("Lower case");
		break;
	default:
		break;
	}

	checkbox_digits->SetValue(m_Startup_Config->UI_CHECKED_checkbox_digits);

	textctrl_other_symbols->AppendText(*m_PassGenerator.GetOtherSymbols());
	if (!m_Startup_Config->UI_CHECKED_checkbox_other_symbols)
	{
		textctrl_other_symbols->Disable();
		checkbox_other_symbols->SetValue(false);
	}
	else
	{
		checkbox_other_symbols->SetValue(true);
	}
	
	textctrl_custom_symbols->AppendText(m_Startup_Config->UI_custom_symbols);
	if (!m_Startup_Config->UI_CHECKED_checkbox_custom_symbols)
	{
		textctrl_custom_symbols->Disable();
		checkbox_custom_symbols->SetValue(false);
	}
	else
	{
		checkbox_custom_symbols->SetValue(true);
	}
	
	textctrl_exclude_symbols->AppendText(m_Startup_Config->UI_exclude_symbols);
	if (!m_Startup_Config->UI_CHECKED_checkbox_exclude_symbols)
	{
		textctrl_exclude_symbols->Disable();
		checkbox_exclude_symbols->SetValue(false);
	}
	else
	{
		checkbox_exclude_symbols->SetValue(true);
	}
	
	spinctrl_pass_leght->SetValue(m_Startup_Config->UI_pass_length);

	textctrl_result->AppendText(m_Startup_Config->UI_previous_pass);

	spinctrl_pass_leght->SetRange(1, 10000);



	// Layout
	sizer_v_charset = new wxStaticBoxSizer(wxVERTICAL, this, "Settings");

	sizer_h_letters = new wxBoxSizer(wxHORIZONTAL);
	sizer_h_letters->Add(checkbox_letters, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer_h_letters->Add(combobox_letter_case, 1, wxLEFT | wxRIGHT, 10);

	sizer_h_other_symbols = new wxBoxSizer(wxHORIZONTAL);
	sizer_h_other_symbols->Add(checkbox_other_symbols, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer_h_other_symbols->Add(textctrl_other_symbols, 1, wxLEFT | wxRIGHT, 10);
	
	sizer_h_custom_symbols = new wxBoxSizer(wxHORIZONTAL);
	sizer_h_custom_symbols->Add(checkbox_custom_symbols, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer_h_custom_symbols->Add(textctrl_custom_symbols, 1, wxLEFT | wxRIGHT, 10);

	sizer_h_exclude_symbols = new wxBoxSizer(wxHORIZONTAL);
	sizer_h_exclude_symbols->Add(checkbox_exclude_symbols, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer_h_exclude_symbols->Add(textctrl_exclude_symbols, 1, wxLEFT | wxRIGHT, 10);

	sizer_h_pass_leght = new wxBoxSizer(wxHORIZONTAL);
	sizer_h_pass_leght->Add(statictext_pass_leght, 1, wxEXPAND | wxLEFT | wxRIGHT, 10);
	sizer_h_pass_leght->Add(spinctrl_pass_leght, 1, wxLEFT | wxRIGHT, 10);
	

	sizer_v_charset->Add(sizer_h_letters, 1, wxEXPAND | wxTOP | wxBOTTOM, 10);
	sizer_v_charset->Add(checkbox_digits, 1, wxEXPAND | wxLEFT | wxRIGHT | wxTOP, 10);
	sizer_v_charset->Add(sizer_h_other_symbols, 1, wxEXPAND | wxTOP, 10);
	sizer_v_charset->Add(sizer_h_custom_symbols, 1, wxEXPAND | wxTOP, 10);
	sizer_v_charset->Add(sizer_h_exclude_symbols, 1, wxEXPAND | wxTOP | wxBOTTOM, 10);
	sizer_v_charset->Add(sizer_h_pass_leght, 1, wxEXPAND | wxTOP | wxBOTTOM, 10);


	sizer_v_bottom = new wxBoxSizer(wxVERTICAL);

	sizer_v_bottom->Add(sizer_v_charset, 1, wxEXPAND | wxALL, 10);
	sizer_v_bottom->Add(textctrl_result, 0, wxEXPAND | wxALL, 7);
	sizer_v_bottom->Add(button_generate, 0, wxEXPAND | wxALL, 7);

	// Set Fonts
	checkbox_letters->SetFont(font_checkbox);
	combobox_letter_case->SetFont(font_checkbox);
	checkbox_digits->SetFont(font_checkbox);
	checkbox_other_symbols->SetFont(font_checkbox);
	textctrl_other_symbols->SetFont(font_checkbox);
	checkbox_custom_symbols->SetFont(font_checkbox);
	textctrl_custom_symbols->SetFont(font_checkbox);
	checkbox_exclude_symbols->SetFont(font_checkbox);
	textctrl_exclude_symbols->SetFont(font_checkbox);
	statictext_pass_leght->SetFont(font_checkbox);
	spinctrl_pass_leght->SetFont(font_checkbox);
	textctrl_result->SetFont(my_font);
	button_generate->SetFont(font_button);
	button_generate->SetFocus();

	this->SetSizerAndFit(sizer_v_bottom);

	Center();
}

void MainFrame::Generate_btn(wxCommandEvent& event)
{
	unsigned int i;
	if (checkbox_letters->IsChecked())
	{
		m_case = combobox_letter_case->GetValue();
		for (i = 0; i < sizeof(m_cases) / sizeof(m_cases[0]); i++)
		{
			if (m_cases[i] == m_case)
			{
				break;
			}
		}
		i += 1;
	}
	else
	{
		i = 0;
	}

	m_useDigits = checkbox_digits->GetValue();
	m_useOtherSymbols = checkbox_other_symbols->GetValue();

	if (checkbox_custom_symbols->GetValue())
	{
		m_customSymbols = textctrl_custom_symbols->GetLineText(0);
	}
	else
	{
		m_customSymbols = "";
	}

	if (checkbox_exclude_symbols->GetValue())
	{
		m_excludeSymbols = textctrl_exclude_symbols->GetLineText(0);
	}
	else
	{
		m_excludeSymbols = "";
	}

	m_passLength = spinctrl_pass_leght->GetValue();

	m_generated_pass = m_PassGenerator.GeneratePass(
		i, 
		m_useDigits, 
		m_useOtherSymbols, 
		m_customSymbols, 
		m_excludeSymbols, 
		m_passLength
	);

	textctrl_result->Clear();
	textctrl_result->AppendText(*m_generated_pass);
	*m_generated_pass = "";

	event.Skip();
}


void MainFrame::OnExit(wxCloseEvent& event)
{
	//wxMessageBox("Good job! Your passwords are incredible!", "[?]", wxOK | wxICON_INFORMATION);
	m_Startup_Config->UI_win_width = GetSize().x;
	m_Startup_Config->UI_win_height = GetSize().y;
	m_Startup_Config->UI_CHECKED_checkbox_letters = checkbox_letters->GetValue();
	m_Startup_Config->UI_CHECKED_checkbox_digits = checkbox_digits->GetValue();
	m_Startup_Config->UI_CHECKED_checkbox_other_symbols = checkbox_other_symbols->GetValue();
	m_Startup_Config->UI_CHECKED_checkbox_custom_symbols = checkbox_custom_symbols->GetValue();
	m_Startup_Config->UI_CHECKED_checkbox_exclude_symbols = checkbox_exclude_symbols->GetValue();
	unsigned int i;
	if (checkbox_letters->IsChecked())
	{
		m_case = combobox_letter_case->GetValue();
		for (i = 0; i < sizeof(m_cases) / sizeof(m_cases[0]); i++)
		{
			if (m_cases[i] == m_case)
			{
				break;
			}
		}
		i += 1;
	}
	else
	{
		i = 0;
	}
	m_Startup_Config->UI_case = i;
	m_Startup_Config->UI_custom_symbols = textctrl_custom_symbols->GetValue();
	m_Startup_Config->UI_exclude_symbols = textctrl_exclude_symbols->GetValue();
	m_Startup_Config->UI_pass_length = spinctrl_pass_leght->GetValue();
	m_Startup_Config->UI_previous_pass = textctrl_result->GetValue();

	m_StartUpConfig.SaveSettings();
	event.Skip();
}
