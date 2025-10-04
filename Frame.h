#pragma once
#include <wx/wx.h>

class Frame :public wxFrame
{
public:
	Frame(const wxString& title);
private:
	void CreateControls();
	void WorkingAddAndEtc();
	void OnAddButtonClicked(wxCommandEvent& evt);
	void AddTaskFromInput();
	void OnInputEnter(wxCommandEvent& evt);
	void OnListKeyPress(wxKeyEvent& evt);
	void DeleteTask();
	void OnClearButtonClicked(wxCommandEvent& evt);
	void Closes(wxCloseEvent& evt);
	void LoadTask();
	void MouseEvent(wxMouseEvent& evt);
	wxPanel* Panel;
	wxStaticText* HeadText;
	wxTextCtrl* InputText;
	wxButton* AddButton;
	wxCheckListBox* CheckListBox;
	wxButton* ClearButton;

};

