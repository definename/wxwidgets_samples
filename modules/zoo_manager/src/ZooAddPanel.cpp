#include "pch.h"
#include "ZooAddPanel.h"

namespace zoo
{

ZooAddPanel::ZooAddPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize()) {
	const int borderSize = 2;
	const wxSize textSize = wxSize(40, wxDefaultPosition.y);
	const wxPoint textPos = wxDefaultPosition;
	long textFlag = wxALIGN_CENTER_VERTICAL | wxUP | wxRIGHT | wxLEFT;

	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	// Name.
	wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
	nameSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Name:"), textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	wxTextCtrl* name = new wxTextCtrl(this, static_cast<int>(CommandId::ID_NAME));
	nameSizer->Add(name, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(nameSizer, 1, wxEXPAND);

	// Gender.
	wxBoxSizer* genderSizer = new wxBoxSizer(wxHORIZONTAL);
	genderSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Gender:"), textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	wxTextCtrl* gender = new wxTextCtrl(this, static_cast<int>(CommandId::ID_GENDER));
	genderSizer->Add(gender, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(genderSizer, 1, wxEXPAND);

	// Age.
	wxBoxSizer* ageSizer = new wxBoxSizer(wxHORIZONTAL);
	ageSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Age:"), textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	wxTextCtrl* age = new wxTextCtrl(this, static_cast<int>(CommandId::ID_AGE));
	ageSizer->Add(age, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(ageSizer, 1, wxEXPAND);

	// Cell.
	wxBoxSizer* cellSizer = new wxBoxSizer(wxHORIZONTAL);
	cellSizer->Add(new wxStaticText(this, wxID_ANY, wxT("Cell:"), textPos, textSize, wxALIGN_RIGHT), 0, textFlag, borderSize);
	wxTextCtrl* cell = new wxTextCtrl(this, static_cast<int>(CommandId::ID_CELL));
	cellSizer->Add(cell, 1, wxEXPAND | wxUP | wxRIGHT | wxLEFT, borderSize);

	topSizer->Add(cellSizer, 1, wxEXPAND);

	// Control buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxHORIZONTAL);
	controlSizer->Add(new wxButton(this, wxID_OK, wxT("Ok")), 0, wxALIGN_BOTTOM | wxUP | wxLEFT | wxDOWN, borderSize);
	controlSizer->Add(new wxButton(this, wxID_CANCEL, wxT("Cancel")), 0, wxALIGN_BOTTOM | wxUP | wxLEFT | wxDOWN, borderSize);

	topSizer->Add(controlSizer, 0, wxSTRETCH_NOT);

	SetSizerAndFit(topSizer);
}

ZooAddPanel::~ZooAddPanel() {

}

} // namespace zoo
