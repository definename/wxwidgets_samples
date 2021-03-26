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
	// Set age.
	void SetAge(const wxString& age) {
		age_->ChangeValue(age);
	}
	// Set cell.
	void SetCell(const wxString& cell) {
		cell_->ChangeValue(cell);
	}
	// Get name.
	wxString GetName() const {
		return name_->GetValue();
	}
	// Get gender.
	wxString GetGender() const {
		return gender_->GetValue();
	}
	// Get age.
	wxString GetAge() const {
		return age_->GetValue();
	}
	// Get cell.
	wxString GetCell() const {
		return cell_->GetValue();
	}

	// Private members.
private:
	// Animal name.
	wxTextCtrl* name_;
	// Animal gender.
	wxTextCtrl* gender_;
	// Animal age.
	wxTextCtrl* age_;
	// Animal cell.
	wxTextCtrl* cell_;
};

};