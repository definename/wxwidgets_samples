#include "pch.h"
#include "GameFramePanel.h"
#include "GameTypes.h"

namespace game
{

class GameGrid : public wxPanel
{
public:
	GameGrid(wxPanel* parent)
	: wxPanel(parent) {
// 		Bind(wxEVT_SIZE, &BasicDrawPane::OnSize, this);
// 		Bind(wxEVT_PAINT, &BasicDrawPane::OnPaint, this);
	}

	void OnPaint(wxPaintEvent& e) {
		wxPaintDC dc(this);
		wxSize size = this->GetClientSize();
		const int border = 5;
		const int title_size = 50;

		dc.SetPen(wxPen(wxColor(0, 0, 0), 3));

		// Vertical
		dc.DrawLine(border, border, border, size.GetHeight() - border);
		dc.DrawLine(border + title_size, border, border + title_size, size.GetHeight() - border);
		dc.DrawLine(((size.GetWidth() - title_size) / 2) + title_size,
					border,
					((size.GetWidth() - title_size) / 2) + title_size,
					size.GetHeight() - border);
		dc.DrawLine(size.GetWidth() - border, border, size.GetWidth() - border, size.GetHeight() - border);

		// Horizontal
		dc.DrawLine(border, border, size.GetWidth() - border, border);
		dc.DrawLine(border, title_size, size.GetWidth() - border, title_size);
		dc.DrawLine(border,
					((size.GetHeight() - title_size) / 2) + title_size,
					size.GetWidth() - border,
					((size.GetHeight() - title_size) / 2) + title_size);
		dc.DrawLine(border, size.GetHeight() - border, size.GetWidth() - border, size.GetHeight() - border);
	}

	void OnSize(wxSizeEvent& e) {
		Refresh();
		e.Skip();
	}
	wxDECLARE_EVENT_TABLE();
};

wxBEGIN_EVENT_TABLE(GameGrid, wxPanel)
	EVT_PAINT(GameGrid::OnPaint)
	EVT_SIZE(GameGrid::OnSize)
wxEND_EVENT_TABLE()

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
	controlSizer->Add(new wxButton(this, GameEvent::ID_PEACE, wxT("Мир")), 1, wxEXPAND);
	controlSizer->Add(new wxButton(this, GameEvent::ID_AGGRESSION, wxT("Агресія")), 1, wxEXPAND);
	palyer1Text_ = new wxStaticText(this, wxID_ANY, wxString::Format(PLAYER1_SCORE_STUB, player1Score_));
	controlSizer->Add(palyer1Text_, 1, wxEXPAND);
	palyer2Text_ = new wxStaticText(this, wxID_ANY, wxString::Format(PLAYER2_SCORE_STUB, player1Score_));
	controlSizer->Add(palyer2Text_, 1, wxEXPAND);

	topSizer->Add(controlSizer, 0, wxEXPAND | wxLEFT | wxUP | wxDOWN, borderSize);

	// Game grid
	wxBoxSizer* gameGrid = new wxBoxSizer(wxHORIZONTAL);
	GameGrid* drawPane = new GameGrid(this);
	gameGrid->Add(drawPane, 1, wxEXPAND);

	topSizer->Add(gameGrid, 1, wxEXPAND);

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
