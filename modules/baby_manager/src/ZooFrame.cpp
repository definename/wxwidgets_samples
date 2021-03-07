#include "pch.h"
#include "ZooFrame.h"
#include "ZooFramePanel.h"
#include "ZooTypes.h"

namespace zoo
{

ZooFrame::ZooFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Zoo Manager"), wxDefaultPosition, wxSize(550, 300), wxDEFAULT_FRAME_STYLE)
	, zooPanel_(new ZooFramePanel(this))
{
	SetIcon(wxICON(IDI_ICON));
	SetMinSize(GetSize());

	// Menu file
	wxMenu* menuFile = new wxMenu;

	wxMenu* menuAnimal = new wxMenu;
	menuAnimal->Append(ZooEvent::ID_ADD, wxT("Add"));
	menuAnimal->Append(ZooEvent::ID_UPDATE, wxT("Update"));
	menuAnimal->Append(ZooEvent::ID_REMOVE, wxT("Remove"));

	menuFile->AppendSubMenu(menuAnimal, wxT("Animal"));

	menuFile->AppendSeparator();
	menuFile->Append(ZooEvent::ID_EXIT, wxT("&Exit"));

	// Menu about
	wxMenu* menuAbout = new wxMenu;
	menuAbout->Append(ZooEvent::ID_ABOUT, wxT("&About"));

	wxMenuBar* menubar = new wxMenuBar;
	menubar->Append(menuFile, wxT("&File"));
	menubar->Append(menuAbout, wxT("&Help"));
	SetMenuBar(menubar);

	Bind(wxEVT_MENU, &ZooFramePanel::OnControl, zooPanel_, ZooEvent::ID_ADD, ZooEvent::ID_REMOVE);
	Bind(wxEVT_MENU, &ZooFrame::OnMenuEvent, this, ZooEvent::ID_EXIT, ZooEvent::ID_ABOUT);
}

void ZooFrame::OnMenuEvent(wxCommandEvent& e)
{
	const ZooEvent menuId = static_cast<ZooEvent>(e.GetId());
	if (menuId == ZooEvent::ID_ABOUT) {
		wxString msg(wxT(
			"Zoo manager\nCreated by Alina Kolomiitseva\nKharkiv 2020\nVersion 1.0.0.1"));
		wxMessageBox(msg, wxT("About"), wxOK | wxCENTRE, this);
	}
	else if (menuId == ZooEvent::ID_EXIT) {
		Close();
	}
}

} // namespace zoo
