#include "pch.h"
#include "GameFramePanel.h"
#include "GameTypes.h"

namespace game
{

#define PLAYER1_SCORE_STUB wxT("Игрок 1: %d")
#define PLAYER2_SCORE_STUB wxT("Игрок 2: %d")

wxBEGIN_EVENT_TABLE(GameFramePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, GameFramePanel::OnControl)
wxEND_EVENT_TABLE()

GameFramePanel::GameFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
	, palyer1Text_(nullptr)
	, palyer2Text_(nullptr)
	, player1Score_(0)
	, player2Score_(0)
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int borderSize = 2;

	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, GameEvent::ID_PEACE, wxT("Мир")), 1, wxSTRETCH_NOT);
	controlSizer->Add(new wxButton(this, GameEvent::ID_AGGRESSION, wxT("Агресія")), 1, wxSTRETCH_NOT);

	topSizer->Add(controlSizer, 0, wxEXPAND | wxUP | wxDOWN | wxRIGHT, borderSize);

	// Score.
	wxBoxSizer* scoreSizer = new wxBoxSizer(wxHORIZONTAL);
	palyer1Text_ = new wxStaticText(this, wxID_ANY, wxString::Format(PLAYER1_SCORE_STUB, player1Score_));
	scoreSizer->Add(palyer1Text_, 1, wxLEFT, 100);
	palyer2Text_ = new wxStaticText(this, wxID_ANY, wxString::Format(PLAYER2_SCORE_STUB, player1Score_));
	scoreSizer->Add(palyer2Text_, 1, wxLEFT, 100);

	topSizer->Add(scoreSizer, 1, wxEXPAND);

	SetSizer(topSizer);
}

void GameFramePanel::OnControl(wxCommandEvent& e) {
	const GameEvent buttonId = static_cast<GameEvent>(e.GetId());
	if (buttonId == GameEvent::ID_PEACE) {
		player1Score_ += 1;
		palyer1Text_->SetLabel(wxString::Format(PLAYER1_SCORE_STUB, player1Score_));
		player2Score_ -= 1;
		palyer2Text_->SetLabel(wxString::Format(PLAYER2_SCORE_STUB, player2Score_));
	}
	else if (buttonId == GameEvent::ID_AGGRESSION) {
		player1Score_ -= 1;
		palyer1Text_->SetLabel(wxString::Format(PLAYER1_SCORE_STUB, player1Score_));
		player2Score_ += 1;
		palyer2Text_->SetLabel(wxString::Format(PLAYER2_SCORE_STUB, player2Score_));
	}
}

} // namespace game
