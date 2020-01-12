#include "pch.h"
#include "ZooFramePanel.h"
#include "ZooList.h"
#include "ZooAddUpdateDialog.h"
#include "ZooTypes.h"

namespace zoo
{

wxBEGIN_EVENT_TABLE(ZooFramePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, ZooFramePanel::OnControl)
wxEND_EVENT_TABLE()

ZooFramePanel::ZooFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
	, zooList_(new ZooList(this)) {

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int border_size = 2;

	// List.
	topSizer->Add(zooList_, 1, wxEXPAND | wxALL, border_size);
	
	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, ZooEvent::ID_ADD, wxT("Add")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, ZooEvent::ID_UPDATE, wxT("Update")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, ZooEvent::ID_REMOVE, wxT("Remove")), 1, wxSTRETCH_NOT);

	topSizer->Add(controlSizer, 0, wxSTRETCH_NOT | wxUP | wxDOWN | wxRIGHT, border_size);

	SetSizer(topSizer);
	zooList_->Update();
}

void ZooFramePanel::OnControl(wxCommandEvent& e) {
	const ZooEvent buttonId = static_cast<ZooEvent>(e.GetId());
	if (buttonId == ZooEvent::ID_ADD) {
		ZooAddUpdateDialog* addDialog = new ZooAddUpdateDialog(this, wxT("Add"));
		if (addDialog->ShowModal() == wxID_OK) {
			ZooDataPtr zooData = addDialog->GetZooData();
			if (!zooList_->AddItem(zooData)) {
				wxMessageBox(wxT("Failed to add item"), wxT("Add item"), wxICON_WARNING, this);
			}
		}
		addDialog->Destroy();
	}
	else if (buttonId == ZooEvent::ID_UPDATE) {
		long index;
		if (zooList_->GetSelectedIndex(index)) {
			ZooDataPtr zooDataOld;
			if (zooList_->GetItem(index, zooDataOld)) {
				ZooAddUpdateDialog* updateDialog = new ZooAddUpdateDialog(this, wxT("Update"), zooDataOld);
				if (updateDialog->ShowModal() == wxID_OK) {
					ZooDataPtr zooData = updateDialog->GetZooData();
					if (!zooList_->UpdateItem(index, zooData)) {
						wxMessageBox(wxT("Failed to update item"), wxT("Update item"), wxICON_WARNING, this);
					}
				}
				updateDialog->Destroy();
			}
			else {
				wxString msg;
				msg.Printf("Failed to retrieve item with given index:%d", index);
				wxMessageBox(msg.ToStdWstring(), wxT("Update item"), wxICON_WARNING, this);
			}
		}
		else {
			wxMessageBox(wxT("Please select item to update"), wxT("Update item"), wxICON_INFORMATION, this);
		}
	} else if (buttonId == ZooEvent::ID_REMOVE) {
		long index;
		if (zooList_->GetSelectedIndex(index)) {
			if (!zooList_->RemoveItem(index)) {
				wxString msg;
				msg.Printf("Failed to remove item with given index:%d", index);
				wxMessageBox(msg.ToStdWstring(), wxT("Remove item"), wxICON_WARNING, this);
			}
		}
		else {
			wxMessageBox(wxT("Please select item to remove"), wxT("Remove item"), wxICON_INFORMATION, this);
		}
	}
}

} // namespace zoo
