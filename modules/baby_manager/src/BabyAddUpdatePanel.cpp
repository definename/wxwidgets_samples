#include "pch.h"
#include "BabyAddUpdatePanel.h"
#include "BabyTypes.h"

namespace baby
{

BabyAddUpdatePanel::BabyAddUpdatePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize()) {

	SetBackgroundColour(BABY_PANEL_COLOUR);

	const int borderSize = 2;
	const wxSize textSize = wxSize(80, wxDefaultPosition.y);
	const wxPoint textPos = wxDefaultPosition;
	long textFlag = wxALIGN_CENTER_VERTICAL | wxUP | wxRIGHT | wxLEFT;

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	// Name.
	wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
	nameSizer->Add(new wxStaticText(this, wxID_ANY, BABY_NAME_COLON, textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	name_ = new wxTextCtrl(this, BabyDataId::ID_NAME);
	nameSizer->Add(name_, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(nameSizer, 1, wxEXPAND);

	// Gender.
	wxBoxSizer* genderSizer = new wxBoxSizer(wxHORIZONTAL);
	genderSizer->Add(new wxStaticText(this, wxID_ANY, BABY_GENDER_COLON, textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	gender_ = new wxTextCtrl(this, BabyDataId::ID_GENDER);
	genderSizer->Add(gender_, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(genderSizer, 1, wxEXPAND);

	// blood.
	wxBoxSizer* bloodSizer = new wxBoxSizer(wxHORIZONTAL);
	bloodSizer->Add(new wxStaticText(this, wxID_ANY, BABY_BLOOD_COLON, textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	blood_ = new wxTextCtrl(this, BabyDataId::ID_BLOOD_TYPE);
	bloodSizer->Add(blood_, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(bloodSizer, 1, wxEXPAND);

	// Apgar.
	wxBoxSizer* apgarSizer = new wxBoxSizer(wxHORIZONTAL);
	apgarSizer->Add(new wxStaticText(this, wxID_ANY, BABY_APGAR_COLON, textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	apgar_ = new wxTextCtrl(this, BabyDataId::ID_APGAR_SCORE);
	apgarSizer->Add(apgar_, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(apgarSizer, 1, wxEXPAND);

	// Control buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
	controlSizer->Add(new wxButton(this, wxID_OK, wxT("Ok")), 0, wxALIGN_BOTTOM | wxUP | wxLEFT | wxDOWN, borderSize);
	controlSizer->Add(new wxButton(this, wxID_CANCEL, wxT("Cancel")), 0, wxALIGN_BOTTOM | wxUP | wxLEFT | wxDOWN, borderSize);

	topSizer->Add(controlSizer, 0, wxSTRETCH_NOT);

	SetSizerAndFit(topSizer);
}

}
