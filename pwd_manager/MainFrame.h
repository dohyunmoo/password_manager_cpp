#pragma once
#include <wx/wx.h>
#include <wx/listctrl.h>

class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
private:
	void Controls();
	void BindEventHandlers();
	void AddSavedPasswords();

	void AddPassword(wxCommandEvent& evt);

	void OnKeyDown(wxKeyEvent& evt);
	void MovePasswords(int offset);
	void Swap(int a, int b);
	void DeletePassword();
	void OnWindowClosed(wxCloseEvent& evt);

	void UpdateEntry();

	void HidePassword(wxCommandEvent& evt);

	wxPanel* panel;
	wxStaticText* headlineText;
	wxTextCtrl* websiteInput;
	wxTextCtrl* usernameInput;
	wxTextCtrl* passwordInput;
	wxButton* addButton;

	wxStaticText* websiteHeader;
	wxStaticText* usernameHeader;
	wxStaticText* passwordHeader;

	wxListBox* entryListBox;
	wxListBox* websiteListBox;
	wxListBox* usernameListBox;
	wxListBox* passwordListBox;

	wxListCtrl* passwordList;
};

