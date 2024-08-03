#include "Application.h"
#include "MainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(Application);

bool Application::OnInit() {
	MainFrame* mainFrame = new MainFrame("Password Manager");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
