#include "App.h"
#include "Frame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool::App::OnInit() {
	Frame* mainFrame = new Frame("To- do List");
	mainFrame->SetClientSize(600, 700);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
