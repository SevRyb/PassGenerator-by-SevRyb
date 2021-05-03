#include "Main.h"
#include "MainFrame.h"
#include "favicon.xpm"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_CLOSE(MainFrame::OnExit)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	MainFrame* main_frame = new MainFrame("PasswordGenerator [ SevRyb ]", wxDefaultPosition, wxDefaultSize);
	SetTopWindow(main_frame);
	main_frame->OnInit(&m_win_width, &m_win_height);
	main_frame->SetIcon(wxIcon(favicon_xpm));
	main_frame->SetBackgroundColour(wxColor(239, 238, 238));
	main_frame->SetSize(wxSize(m_win_width, m_win_height));
	main_frame->Show(true);
	return true;
}