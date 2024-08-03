#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void Controls();
	void BindEventHandlers();

	void Add(wxCommandEvent& evt);
	void AddPassword();

	void KeyDown(wxKeyEvent& evt);
	void MovePasswords(int offset);
	void Swap(int a, int b);
	void DeletePassword();
	void DeleteButtonClicked(wxCommandEvent& evt);

	void HidePassword(wxCommandEvent& evt);

	wxPanel* panel;
	wxStaticText* headlineText;
	wxTextCtrl* websiteInput;
	wxTextCtrl* usernameInput;
	wxTextCtrl* passwordInput;
	wxButton* addButton;
	wxButton* deleteButton;

	wxStaticText* websiteHeader;
	wxStaticText* usernameHeader;
	wxStaticText* passwordHeader;

	wxListBox* websiteListBox;
	wxListBox* usernameListBox;
	wxListBox* passwordListBox;
	wxCheckListBox* deleteListBox;
};

