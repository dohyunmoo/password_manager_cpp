#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/listctrl.h>
#include <vector>
#include <string>
#include "Password.h"
#include <format>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	Controls();
	BindEventHandlers();
	AddSavedPasswords();

	CreateStatusBar();
}

void MainFrame::HidePassword(wxCommandEvent& evt)
{
	wxLogStatus("toggled");
}

void MainFrame::BindEventHandlers()
{
	addButton->Bind(wxEVT_BUTTON, &MainFrame::AddPassword, this);
	entryListBox->Bind(wxEVT_KEY_DOWN, &MainFrame::OnKeyDown, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnWindowClosed, this);
}

void MainFrame::AddSavedPasswords()
{
	std::vector<Password> passwords = LoadPassword("passwords.txt");

	int index = 0;

	for (const Password& password : passwords)
	{
		//passwordList->InsertItem(0, password.website);
		//passwordList->SetItem(index, 1, password.username);
		//passwordList->SetItem(index, 2, password.password);
		websiteListBox->Insert(password.website, index);
		usernameListBox->Insert(password.username, index);
		passwordListBox->Insert(password.password, index);

		entryListBox->Insert(wxString::Format(wxT("%i"), entryListBox->GetCount() + 1), index);

		index++;
	}
}

void MainFrame::AddPassword(wxCommandEvent& evt)
{
	wxString website = websiteInput->GetValue();
	wxString username = usernameInput->GetValue();
	wxString password = passwordInput->GetValue();
	wxString deleteKey = "del";

	if (!website.IsEmpty() && !username.IsEmpty() && !password.IsEmpty()) {
		websiteListBox->Insert(website, websiteListBox->GetCount());
		usernameListBox->Insert(username, usernameListBox->GetCount());
		passwordListBox->Insert(password, passwordListBox->GetCount());
		
		entryListBox->Insert(wxString::Format(wxT("%i"), entryListBox->GetCount() + 1), entryListBox->GetCount());

		//int index = passwordList->GetItemCount();

		//passwordList->InsertItem(index, website);
		//passwordList->SetItem(index, 1, username);
		//passwordList->SetItem(index, 2, password);

		websiteInput->Clear();
		usernameInput->Clear();
		passwordInput->Clear();
	}
	else if (website.IsEmpty() && username.IsEmpty() && password.IsEmpty()) {
		wxLogStatus("input fields are empty");
	}
	else {
		wxLogStatus("not all input fields filled");
	}
}

void MainFrame::OnKeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) {
	case WXK_DELETE:
		DeletePassword();
		break;
	case WXK_UP:
		MovePasswords(-1);
		break;
	case WXK_DOWN:
		MovePasswords(1);
		break;
	}
}

void MainFrame::OnWindowClosed(wxCloseEvent& evt)
{
	std::vector<Password> passwords;

	for (int i = 0; i < websiteListBox->GetCount(); i++) {
		Password password;
		password.website = websiteListBox->GetString(i).ToStdString();
		password.username = usernameListBox->GetString(i).ToStdString();
		password.password = passwordListBox->GetString(i).ToStdString();
		passwords.push_back(password);
	}

	SavePassword(passwords, "passwords.txt");
	evt.Skip();
}

void MainFrame::UpdateEntry()
{
	for (int i = 0; i < entryListBox->GetCount(); i++) {
		entryListBox->SetString(i, wxString::Format(wxT("%i"), i + 1));
	}
}

void MainFrame::DeletePassword()
{
	if (entryListBox->GetSelection() == wxNOT_FOUND) {
		return;
	}

	wxMessageDialog dialog(this, "Are you sure you want to delete all the selected passwords?", "Delete", wxYES_NO | wxCANCEL);

	int result = dialog.ShowModal();

	if (result == wxID_YES) {
		int index = entryListBox->GetSelection();
		std::string web = websiteListBox->GetString(index).ToStdString();
		websiteListBox->Delete(index);
		usernameListBox->Delete(index);
		passwordListBox->Delete(index);

		entryListBox->Delete(index);
		UpdateEntry();

		std::string logMessage = std::format("password entry {} : \"{}\" is deleted", index + 1, web);

		wxLogStatus(wxString::FromUTF8(logMessage));
	}
}

void MainFrame::MovePasswords(int offset)
{
	int selectedIndex = websiteListBox->GetSelection();

	if (selectedIndex == wxNOT_FOUND) {
		return;
	}

	int newIndex = selectedIndex + offset;

	if (newIndex >= 0 && newIndex < websiteListBox->GetCount()) {
		Swap(selectedIndex, newIndex);
		websiteListBox->SetSelection(newIndex, true);
	}
}

void MainFrame::Swap(int a, int b)
{
	Password passwordA{ websiteListBox->GetString(a).ToStdString(), usernameListBox->GetString(a).ToStdString(), passwordListBox->GetString(a).ToStdString() };
	Password passwordB{ websiteListBox->GetString(b).ToStdString(), usernameListBox->GetString(b).ToStdString(), passwordListBox->GetString(b).ToStdString() };

	websiteListBox->SetString(a, passwordB.website);
	usernameListBox->SetString(a, passwordB.username);
	passwordListBox->SetString(a, passwordB.password);

	websiteListBox->SetString(b, passwordA.website);
	usernameListBox->SetString(b, passwordA.username);
	passwordListBox->SetString(b, passwordA.password);
}

void MainFrame::Controls() {
	wxFont headlineFont(wxFontInfo(wxSize(0, 36)).Bold());
	wxFont mainFont(wxFontInfo(wxSize(0, 16)));

	panel = new wxPanel(this);
	panel->SetFont(mainFont);

	headlineText = new wxStaticText(panel, wxID_ANY, "Dohyun's Password Manager", wxPoint(0, 22), wxSize(800, -1), wxALIGN_CENTER_HORIZONTAL);
	headlineText->SetFont(headlineFont);

	int entry_width = 30;
	int w_width = 200;
	int up_width = 170;
	int add_width = 75;
	int del_width = 125;

	websiteHeader = new wxStaticText(panel, wxID_ANY, "Website", wxPoint(50, 80), wxSize(w_width, -1), wxALIGN_CENTER_HORIZONTAL);
	usernameHeader = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(265, 80), wxSize(up_width, -1), wxALIGN_CENTER_HORIZONTAL);
	passwordHeader = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(450, 80), wxSize(up_width, -1), wxALIGN_CENTER_HORIZONTAL);

	websiteInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(50, 100), wxSize(w_width, 24));
	usernameInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(265, 100), wxSize(up_width, 24));
	passwordInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(450, 100), wxSize(up_width, 24));

	addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(700, 100), wxSize(add_width, 24));

	entryListBox = new wxListBox(panel, wxID_ANY, wxPoint(10, 130), wxSize(entry_width, 400));
	websiteListBox = new wxListBox(panel, wxID_ANY, wxPoint(50, 130), wxSize(w_width, 400));
	usernameListBox = new wxListBox(panel, wxID_ANY, wxPoint(265, 130), wxSize(up_width, 400));
	passwordListBox = new wxListBox(panel, wxID_ANY, wxPoint(450, 130), wxSize(up_width, 400));	
}