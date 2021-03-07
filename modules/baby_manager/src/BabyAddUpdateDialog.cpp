#include "pch.h"
#include "BabyAddUpdateDialog.h"
#include "BabyAddUpdatePanel.h"
#include "BabyTypes.h"

namespace baby
{

BabyAddUpdateDialog::BabyAddUpdateDialog(wxWindow* parent, const wxString& title, const BabyDataPtr zooData /*= nullptr*/)
	: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(400, 180))
	, addUpdatePanel_(new BabyAddUpdatePanel(this)) {

	if (zooData) {
		addUpdatePanel_->SetName(zooData->name_);
		addUpdatePanel_->SetGender(zooData->gender_);
		addUpdatePanel_->SetAge(zooData->age_);
		addUpdatePanel_->SetCell(zooData->cell_);
	}
}

BabyAddUpdateDialog::~BabyAddUpdateDialog() {

}

BabyDataPtr BabyAddUpdateDialog::GetZooData() const {
	BabyDataPtr zooData = std::make_shared<BabyData>(
		addUpdatePanel_->GetName().ToStdWstring(),
		addUpdatePanel_->GetGender().ToStdWstring(),
		addUpdatePanel_->GetAge().ToStdWstring(),
		addUpdatePanel_->GetCell().ToStdWstring());
	return zooData;
}

}
