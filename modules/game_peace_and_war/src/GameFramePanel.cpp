#include "pch.h"
#include "GameFramePanel.h"
#include "GameTypes.h"

namespace game
{

wxBEGIN_EVENT_TABLE(GameFramePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, GameFramePanel::OnControl)
wxEND_EVENT_TABLE()

GameFramePanel::GameFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize()) {
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int border_size = 2;

	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, GameEvent::ID_PEACE, wxT("Мир")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, GameEvent::ID_AGGRESSION, wxT("Агресія")), 1, wxSTRETCH_NOT);

	topSizer->Add(controlSizer, 0, wxEXPAND | wxUP | wxDOWN | wxRIGHT, border_size);

	SetSizer(topSizer);
}

void GameFramePanel::OnControl(wxCommandEvent& e) {
	const GameEvent buttonId = static_cast<GameEvent>(e.GetId());
	if (buttonId == GameEvent::ID_PEACE) {
		wxMessageBox(wxT("ID_PEACE"), wxT("ID_PEACE_1"), wxICON_WARNING, this);
	}
	else if (buttonId == GameEvent::ID_AGGRESSION) {
		wxMessageBox(wxT("ID_AGGRESSION"), wxT("ID_AGGRESSION_2"), wxICON_WARNING, this);
	}
}

} // namespace game
