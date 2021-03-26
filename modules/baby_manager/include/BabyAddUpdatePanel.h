#pragma once

namespace baby
{

class BabyAddUpdatePanel: public wxPanel
{
	// Construction and destruction.
public:
	// Constructor.
	BabyAddUpdatePanel(wxWindow* parent);
	// Destructor.
	~BabyAddUpdatePanel() = default;

	// Public interface.
public:
	// Set name.
	void SetName(const wxString& name) {
		name_->ChangeValue(name);
	}
	// Set gender.
	void SetGender(const wxString& gender) {
		gender_->ChangeValue(gender);
	}
	// Set blood.
	void SetBlood(const wxString& blood) {
		blood_->ChangeValue(blood);
	}
	// Set apgar.
	void SetApgar(const wxString& apgar) {
		apgar_->ChangeValue(apgar);
	}
	// Get name.
	wxString GetName() const {
		return name_->GetValue();
	}
	// Get gender.
	wxString GetGender() const {
		return gender_->GetValue();
	}
	// Get blood.
	wxString GetBlood() const {
		return blood_->GetValue();
	}
	// Get apgar.
	wxString GetApgar() const {
		return apgar_->GetValue();
	}

	// Private members.
private:
	// Name.
	wxTextCtrl* name_;
	// Gender.
	wxTextCtrl* gender_;
	// Blood.
	wxTextCtrl* blood_;
	// Apgar.
	wxTextCtrl* apgar_;
};

};