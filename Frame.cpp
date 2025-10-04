#include "Frame.h"
#include "Task.h"
#include <wx/wx.h>
#include <string>
#include <vector>
using namespace std;

Frame::Frame(const wxString& title):wxFrame(nullptr, wxID_ANY,title) {
	CreateControls();
	SizeW();
	WorkingAddAndEtc();
	LoadTask();
}

void Frame::CreateControls()
{
	wxFont HeadLineFont(wxFontInfo(wxSize(0, 36)));
	wxFont MainFont(wxFontInfo(wxSize(0, 24)));

	Panel = new wxPanel(this);
	Panel->SetFont(MainFont);

	HeadText = new wxStaticText(Panel, wxID_ANY, "To-do List");
	HeadText->SetFont(HeadLineFont);
	HeadText->SetBackgroundColour(*wxGREEN);//������ ������ :�


	ClearButton = new wxButton(Panel, wxID_ANY, "Clear");
	AddButton = new wxButton(Panel, wxID_ANY, "Add");//������ �� SWAG
	InputText = new wxTextCtrl(Panel, wxID_ANY, "",wxDefaultPosition,wxDefaultSize, wxTE_PROCESS_ENTER);
	CheckListBox = new wxCheckListBox(Panel, wxID_ANY);
	
	
	
}

void Frame::WorkingAddAndEtc()
{
	AddButton->Bind(wxEVT_BUTTON, &Frame::OnAddButtonClicked,this); 
	InputText -> Bind(wxEVT_TEXT_ENTER, &Frame::OnInputEnter, this);
	CheckListBox->Bind(wxEVT_KEY_DOWN, &Frame::OnListKeyPress, this);
	CheckListBox->Bind(wxEVT_RIGHT_DOWN, &Frame::MouseEvent, this);
	ClearButton->Bind(wxEVT_BUTTON, &Frame::OnClearButtonClicked, this);
	this->Bind(wxEVT_CLOSE_WINDOW, &Frame::Closes, this);
}

void Frame::OnAddButtonClicked(wxCommandEvent& evt)
{
	AddTaskFromInput();
}

void Frame::AddTaskFromInput()
{
	wxString description = InputText->GetValue();
	if (!description.IsEmpty()) {
		CheckListBox->Insert(description, CheckListBox->GetCount());
		InputText->Clear();
	}
	InputText->SetFocus();
}

void Frame::OnInputEnter(wxCommandEvent& evt)
{
	AddTaskFromInput();
}

void Frame::OnListKeyPress(wxKeyEvent& evt)
{
	if (evt.GetKeyCode()== WXK_DELETE) {
		DeleteTask();
		
	}
}

void Frame::DeleteTask()
{

	int SelectedIndex = CheckListBox->GetSelection();
	if (SelectedIndex == wxNOT_FOUND) {
		return;
	}
	CheckListBox->Delete(SelectedIndex);
}

void Frame::OnClearButtonClicked(wxCommandEvent& evt)
{
	if (CheckListBox->IsEmpty()) {
		return;
	}
	CheckListBox->Clear();
}

void Frame::Closes(wxCloseEvent& evt)
{
	vector <Task> tasks;
	for (int i = 0; i < CheckListBox->GetCount(); i++) {
		Task task;
		task.Set_Description(CheckListBox->GetString(i).ToStdString());
		task.Set_Done (CheckListBox->IsChecked(i));
		tasks.push_back(task);
	}
	SaveTasksToFile(tasks, "tasks.txt");
	evt.Skip();
}

void Frame::LoadTask()
{
	vector<Task>tasks = LoadTasksFromFile("tasks.txt");
	for (const Task& task : tasks) {
		int index = CheckListBox->GetCount();
		
		CheckListBox->Insert(task.Get_Description(), index);
		CheckListBox->Check(index, task.Get_Done());
		
	}

}

void Frame::MouseEvent(wxMouseEvent& evt)
{
	DeleteTask();
}

void Frame::SizeW()
{
	wxBoxSizer* size = new wxBoxSizer(wxVERTICAL);
	size->Add(HeadText, wxSizerFlags().CenterHorizontal());
	size->AddSpacer(25);
	wxBoxSizer* inputsize = new wxBoxSizer(wxHORIZONTAL);
	inputsize->Add(InputText,wxSizerFlags().Proportion(1));
	inputsize->Add(AddButton);
	size->Add(inputsize,wxSizerFlags().Expand());
	size->AddSpacer(5);
	size->Add(CheckListBox, wxSizerFlags().Expand().Proportion(1));
	size->AddSpacer(10);
	size->Add(ClearButton, wxSizerFlags().CenterHorizontal());
	size->AddSpacer(50);

	wxGridSizer* bsize = new wxGridSizer(1);
	bsize->Add(size, wxSizerFlags().Border(wxALL, 30).Expand());
	Panel->SetSizer(bsize);
	bsize->SetSizeHints(this);
}

