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

BabyDataPtr BabyAddUpdateDialog::GetBabyData() const {
	BabyDataPtr data = nullptr;

	wxString name = addUpdatePanel_->GetName().MakeCapitalized();
	wxString gender = addUpdatePanel_->GetGender().MakeLower();
	wxString blood = addUpdatePanel_->GetBlood().MakeUpper();

	long apgar = APGAR_MIN;
	addUpdatePanel_->GetApgar().ToLong(&apgar);
	if (apgar < APGAR_MIN || apgar > APGAR_MAX) {
		wxMessageBox(wxT("Invalid Apgar score given"), wxT("Apgare score check"), wxICON_WARNING, this->GetParent());
	} else if (gender.Cmp(GENDER_MALE) != 0 && gender.Cmp(GENDER_FEMALE) != 0) {
		wxMessageBox(wxT("Invalid gender given"), wxT("Gender check"), wxICON_WARNING, this->GetParent());
	} else if (blood.Cmp(BLOOD_0) != 0 && blood.Cmp(BLOOD_A) != 0 && blood.Cmp(BLOOD_B) != 0 && blood.Cmp(BLOOD_AB) != 0) {
		wxMessageBox(wxT("Invalid blood given"), wxT("Blood check"), wxICON_WARNING, this->GetParent());
	} else {
		data.reset(new BabyDataPtr::element_type(
			name.ToStdWstring(),
			gender.ToStdWstring(),
			blood.ToStdWstring(),
			addUpdatePanel_->GetApgar().ToStdWstring()));
	}

	return data;
}

}
