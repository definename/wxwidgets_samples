#include "pch.h"
#include "BabyFramePanel.h"
#include "BabyList.h"
#include "BabyAddUpdateDialog.h"
#include "BabyTypes.h"

namespace baby
{

wxBEGIN_EVENT_TABLE(BabyFramePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, BabyFramePanel::OnControl)
wxEND_EVENT_TABLE()

BabyFramePanel::BabyFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
	, list_(new BabyList(this)) {

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int border_size = 2;

	// List.
	topSizer->Add(list_, 1, wxEXPAND | wxALL, border_size);
	
	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, BabyEvent::ID_ADD, wxT("Add")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, BabyEvent::ID_UPDATE, wxT("Update")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, BabyEvent::ID_REMOVE, wxT("Remove")), 1, wxSTRETCH_NOT);

	topSizer->Add(controlSizer, 0, wxSTRETCH_NOT | wxUP | wxDOWN | wxRIGHT, border_size);

	SetSizer(topSizer);
	list_->Update();
}

void BabyFramePanel::OnControl(wxCommandEvent& e) {
	const BabyEvent buttonId = static_cast<BabyEvent>(e.GetId());
	if (buttonId == BabyEvent::ID_ADD) {
		BabyAddUpdateDialog* addDialog = new BabyAddUpdateDialog(this, wxT("Add"));
		if (addDialog->ShowModal() == wxID_OK) {
			list_->AddItem(addDialog->GetBabyData());
		}
		addDialog->Destroy();
	} else if (buttonId == BabyEvent::ID_UPDATE) {
		long index;
		if (list_->GetSelectedIndex(index)) {
			BabyDataPtr dataOld;
			if (list_->GetItem(index, dataOld)) {
				BabyAddUpdateDialog* updateDialog = new BabyAddUpdateDialog(this, wxT("Update"), dataOld);
				if (updateDialog->ShowModal() == wxID_OK) {
					list_->UpdateItem(index, updateDialog->GetBabyData());
				}
				updateDialog->Destroy();
			} else {
				wxString msg;
				msg.Printf("Failed to retrieve item with given index:%d", index);
				wxMessageBox(msg.ToStdWstring(), wxT("Update item"), wxICON_WARNING, this);
			}
		} else {
			wxMessageBox(wxT("Please select item to update"), wxT("Update item"), wxICON_INFORMATION, this);
		}
	} else if (buttonId == BabyEvent::ID_REMOVE) {
		long index;
		if (list_->GetSelectedIndex(index)) {
			list_->RemoveItem(index);
		} else {
			wxMessageBox(wxT("Please select item to remove"), wxT("Remove item"), wxICON_INFORMATION, this);
		}
	}
}

}
