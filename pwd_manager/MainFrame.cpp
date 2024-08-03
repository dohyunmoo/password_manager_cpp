#include "MainFrame.h"
#include <wx/wx.h>
#include <vector>
#include <string>
#include "Password.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	Controls();
	BindEventHandlers();

	CreateStatusBar();

	// wxTextCtrl* text2 = new wxTextCtrl(panel, wxID_ANY, "Editable Text", wxPoint(150, 150), wxSize(200, -1));
}

void MainFrame::HidePassword(wxCommandEvent& evt)
{
	wxLogStatus("toggled");
}

void MainFrame::BindEventHandlers()
{
	addButton->Bind(wxEVT_BUTTON, &MainFrame::Add, this);
	deleteButton->Bind(wxEVT_BUTTON, &MainFrame::DeleteButtonClicked, this);
}

void MainFrame::Add(wxCommandEvent& evt)
{
	AddPassword();
}

void MainFrame::AddPassword()
{
	wxString website = websiteInput->GetValue();
	wxString username = usernameInput->GetValue();
	wxString password = passwordInput->GetValue();
	wxString deleteKey = "del";

	if (!website.IsEmpty() && !username.IsEmpty() && !password.IsEmpty()) {
		websiteListBox->Insert(website, websiteListBox->GetCount());
		usernameListBox->Insert(username, usernameListBox->GetCount());
		passwordListBox->Insert(password, passwordListBox->GetCount());
		deleteListBox->Insert(deleteKey, deleteListBox->GetCount());

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

void MainFrame::KeyDown(wxKeyEvent& evt)
{
	switch (evt.GetKeyCode()) {
		case WXK_UP:
			MovePasswords(-1);
			break;
		case WXK_DOWN:
			MovePasswords(1);
			break;
	}
}

void MainFrame::DeleteButtonClicked(wxCommandEvent& evt) {
	if (deleteListBox->IsEmpty()) {
		return;
	}

	wxMessageDialog dialog(this, "Are you sure you want to delete all the selected passwords?", "Delete", wxYES_NO | wxCANCEL);

	int result = dialog.ShowModal();

	if (result == wxID_YES) {
		DeletePassword();
	}
}

void MainFrame::DeletePassword()
{
	unsigned int listLength = deleteListBox->GetCount() - 1;

	while (listLength >= 0) {
		if (deleteListBox->IsChecked(listLength)) {
			deleteListBox->Delete(listLength);
			websiteListBox->Delete(listLength);
			usernameListBox->Delete(listLength);
			passwordListBox->Delete(listLength);
		}
		listLength--;
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
	headlineText->SetBackgroundColour(*wxRED);

	int w_width = 200;
	int up_width = 170;
	int add_width = 75;
	int del_width = 125;

	websiteHeader = new wxStaticText(panel, wxID_ANY, "Website", wxPoint(10, 80), wxSize(w_width, -1), wxALIGN_CENTER_HORIZONTAL);
	usernameHeader = new wxStaticText(panel, wxID_ANY, "Username", wxPoint(225, 80), wxSize(up_width, -1), wxALIGN_CENTER_HORIZONTAL);
	passwordHeader = new wxStaticText(panel, wxID_ANY, "Password", wxPoint(410, 80), wxSize(up_width, -1), wxALIGN_CENTER_HORIZONTAL);

	websiteInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(10, 100), wxSize(w_width, 24));
	usernameInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(225, 100), wxSize(up_width, 24));
	passwordInput = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(410, 100), wxSize(up_width, 24));

	websiteListBox = new wxListBox(panel, wxID_ANY, wxPoint(10, 130), wxSize(w_width, 400));
	usernameListBox = new wxListBox(panel, wxID_ANY, wxPoint(225, 130), wxSize(up_width, 400));
	passwordListBox = new wxListBox(panel, wxID_ANY, wxPoint(410, 130), wxSize(up_width, 400));
	deleteListBox = new wxCheckListBox(panel, wxID_ANY, wxPoint(600, 130), wxSize(50, 400));

	addButton = new wxButton(panel, wxID_ANY, "Add", wxPoint(700, 100), wxSize(add_width, 24));
	deleteButton = new wxButton(panel, wxID_ANY, "Delete Checked", wxPoint(10, 550), wxSize(del_width, 24));
}