#include "pch.h"
#include "ZooListPanel.h"
#include "ZooList.h"
#include "ZooAddDialog.h"

namespace zoo
{

wxBEGIN_EVENT_TABLE(ZooListPanel, wxPanel)
	EVT_BUTTON(wxID_ANY, ZooListPanel::OnControl)
wxEND_EVENT_TABLE()

ZooListPanel::ZooListPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
	, zooList_(new ZooList(this)) {

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int border_size = 2;

	topSizer->Add(zooList_, 1, wxEXPAND | wxALL, border_size);
	
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, static_cast<int>(CommandId::ID_ADD), wxT("Add")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, static_cast<int>(CommandId::ID_REMOVE), wxT("Remove")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, static_cast<int>(CommandId::ID_UPDATE), wxT("Update")), 1, wxSTRETCH_NOT);

	topSizer->Add(controlSizer, 0, wxSTRETCH_NOT | wxUP | wxDOWN | wxRIGHT, border_size);

	SetSizer(topSizer);
}

ZooListPanel::~ZooListPanel() {
}

void ZooListPanel::OnControl(wxCommandEvent& e) {
	const CommandId buttonId = static_cast<CommandId>(e.GetId());
	if (buttonId == CommandId::ID_ADD) {
		ZooAddDialog* addDialog = new ZooAddDialog(this);
		if (addDialog->ShowModal() == wxID_OK) {

		}
		addDialog->Destroy();
	}
	else if (buttonId == CommandId::ID_REMOVE) {
		wxMessageBox(wxT("remove"), wxT("Info"), wxICON_INFORMATION);
	}
	else if (buttonId == CommandId::ID_UPDATE) {
		wxMessageBox(wxT("update"), wxT("Info"), wxICON_INFORMATION);
	}
}

} // namespace zoo
