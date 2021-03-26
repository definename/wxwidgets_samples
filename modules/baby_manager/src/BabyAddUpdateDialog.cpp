#include "pch.h"
#include "BabyAddUpdateDialog.h"
#include "BabyAddUpdatePanel.h"
#include "BabyTypes.h"

namespace baby
{

BabyAddUpdateDialog::BabyAddUpdateDialog(wxWindow* parent, const wxString& title, const BabyDataPtr data /*= nullptr*/)
	: wxDialog(parent, wxID_ANY, title, wxDefaultPosition, wxSize(400, 180))
	, addUpdatePanel_(new BabyAddUpdatePanel(this)) {

	if (data) {
		addUpdatePanel_->SetName(data->name_);
		addUpdatePanel_->SetGender(data->gender_);
		addUpdatePanel_->SetBlood(data->blood_);
		addUpdatePanel_->SetApgar(data->apgar_);
	}
}

BabyDataPtr BabyAddUpdateDialog::GetZooData() const {
	BabyDataPtr data = std::make_shared<BabyData>(
		addUpdatePanel_->GetName().ToStdWstring(),
		addUpdatePanel_->GetGender().ToStdWstring(),
		addUpdatePanel_->GetBlood().ToStdWstring(),
		addUpdatePanel_->GetApgar().ToStdWstring());
	return data;
}

}
