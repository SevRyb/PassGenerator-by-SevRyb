#pragma once
#include <wx/wx.h>

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
private:
	int m_win_width = 0;
	int m_win_height = 0;
};