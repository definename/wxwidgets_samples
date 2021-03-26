#include "pch.h"
#include "BabyFrame.h"
#include "BabyFramePanel.h"
#include "BabyTypes.h"

namespace baby
{

BabyFrame::BabyFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Baby Manager"), wxDefaultPosition, wxSize(550, 300), wxDEFAULT_FRAME_STYLE)
	, panel_(new BabyFramePanel(this))
{
	SetIcon(wxICON(IDI_ICON));
	SetMinSize(GetSize());

	// Menu file
	wxMenu* menuFile = new wxMenu;

	wxMenu* menuAnimal = new wxMenu;
	menuAnimal->Append(BabyEvent::ID_ADD, wxT("Add"));
	menuAnimal->Append(BabyEvent::ID_UPDATE, wxT("Update"));
	menuAnimal->Append(BabyEvent::ID_REMOVE, wxT("Remove"));

	menuFile->AppendSubMenu(menuAnimal, wxT("Baby"));

	menuFile->AppendSeparator();
	menuFile->Append(BabyEvent::ID_EXIT, wxT("&Exit"));

	// Menu about
	wxMenu* menuAbout = new wxMenu;
	menuAbout->Append(BabyEvent::ID_ABOUT, wxT("&About"));

	wxMenuBar* menubar = new wxMenuBar;
	menubar->Append(menuFile, wxT("&File"));
	menubar->Append(menuAbout, wxT("&Help"));
	SetMenuBar(menubar);

	Bind(wxEVT_MENU, &BabyFramePanel::OnControl, panel_, BabyEvent::ID_ADD, BabyEvent::ID_REMOVE);
	Bind(wxEVT_MENU, &BabyFrame::OnMenuEvent, this, BabyEvent::ID_EXIT, BabyEvent::ID_ABOUT);
}

void BabyFrame::OnMenuEvent(wxCommandEvent& e)
{
	const BabyEvent menuId = static_cast<BabyEvent>(e.GetId());
	if (menuId == BabyEvent::ID_ABOUT) {
		wxMessageBox(BABY_MGR_ABOUT, wxT("About"), wxOK | wxCENTRE, this);
	}
	else if (menuId == BabyEvent::ID_EXIT) {
		Close();
	}
}

}
