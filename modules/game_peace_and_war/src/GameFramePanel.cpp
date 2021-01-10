#include "pch.h"
#include "GameFramePanel.h"
#include "GameTypes.h"

#define PLAYER1_SCORE_STUB wxT("Игрок 1: %d")
#define PLAYER2_SCORE_STUB wxT("Игрок 2: %d")
#define CONFLICT_PEACE wxT("Мир")
#define CONFLICT_AGGRESION wxT("Агрессия")
#define CONFLICT_OPTIMAL wxT("Оптимальная стратегия")

namespace game
{

class GameGrid : public wxPanel
{
public:
	GameGrid(wxPanel* parent)
	: wxPanel(parent)
	, strategy_{{ {0, 0}, { -1, 2 } }, { {2, -1}, {1, 1} }}
	, select_("none"){
	}

	std::pair<int, int> DoGame(const int player1_choice, const int player2_choice) {
		select_.clear();
		select_.append(std::to_string(player1_choice));
		select_.append(std::to_string(player2_choice));
		PaintNow();
		return strategy_[player1_choice][player2_choice];
	}

	void DoOptimal() {
		std::string select_min1 = "00";
		int min1 = strategy_[0][0].first;
		if (min1 > strategy_[0][1].first) {
			min1 = strategy_[0][1].first;
			select_min1 = "01";
		}

		std::string select_min2 = "10";
		int min2 = strategy_[1][0].first;
		if (min2 > strategy_[1][1].first) {
			min2 = strategy_[1][1].first;
			select_min2 = "11";
		}

		
		int max1 = min1;
		select_ = select_min1;
		if (max1 < min2) {
			max1 = min2;
			select_ = select_min2;
		}
		PaintNow();
	}

	void PaintNow()
	{
		wxClientDC dc(this);
		Render(dc);
	}

	void OnPaint(wxPaintEvent& e) {
		wxPaintDC dc(this);
		Render(dc);
	}

	void Render(wxDC & dc) {
		wxSize size = this->GetClientSize();
		const int border = 5;
		const int title_size = 50;

		dc.Clear();
		dc.SetPen(wxPen(wxColor(0, 0, 0), 1));
		auto brush = dc.GetBrush();
		dc.SetBrush(*wxGREEN_BRUSH);
		wxCoord width = ((size.GetWidth() - title_size) / 2);
		wxCoord height = ((size.GetHeight() - title_size) / 2);

		if (select_.compare("00") == 0) { // 00
			dc.DrawRectangle(
				border + title_size,
				title_size,
				width - border,
				height);
		}
		else if (select_.compare("10") == 0) { // 10
			dc.DrawRectangle(
				border + title_size,
				((size.GetHeight() - title_size) / 2) + title_size,
				width - border,
				height - border);
		}
		else if (select_.compare("01") == 0) { // 01
			dc.DrawRectangle(
				((size.GetWidth() - title_size) / 2) + title_size,
				title_size,
				width - border,
				height);
		}
		else if (select_.compare("11") == 0) { // 11
			dc.DrawRectangle(
				((size.GetWidth() - title_size) / 2) + title_size,
				((size.GetHeight() - title_size) / 2) + title_size,
				width - border,
				height - border);
		}

		dc.SetPen(wxPen(wxColor(0, 0, 0), 3));
		dc.SetBrush(brush);

		// Horizontal text
		dc.DrawText(CONFLICT_PEACE, title_size + border * 2, title_size / 2);
		dc.DrawText(CONFLICT_AGGRESION, (((size.GetWidth() - title_size) / 2) + title_size) + border, title_size / 2);

		// Vertical text
		dc.DrawRotatedText(
			CONFLICT_PEACE,
			title_size / 2,
			(((size.GetHeight() - title_size) / 2) + title_size) - border,
			90.0);
		dc.DrawRotatedText(
			CONFLICT_AGGRESION,
			title_size / 2,
			size.GetHeight() - border * 2,
			90.0);

		// Set strategy1
		dc.DrawText(
			wxString::Format("%d", strategy_[0][0].first),
			title_size + border * 2,
			((size.GetHeight() - title_size) / 2));
		dc.DrawText(
			wxString::Format("%d", strategy_[0][1].first),
			(((size.GetWidth() - title_size) / 2) + title_size) + border,
			((size.GetHeight() - title_size) / 2));
		dc.DrawText(
			wxString::Format("%d", strategy_[1][0].first),
			title_size + border * 2,
			size.GetHeight() - title_size);
		dc.DrawText(
			wxString::Format("%d", strategy_[1][1].first),
			(((size.GetWidth() - title_size) / 2) + title_size) + border,
			size.GetHeight() - title_size);

		// Set strategy2
		dc.DrawText(
			wxString::Format("%d", strategy_[0][0].second),
			(((size.GetWidth() - title_size) / 2) + title_size) - 40,
			title_size * 2);
		dc.DrawText(
			wxString::Format("%d", strategy_[0][1].second),
			(size.GetWidth() - border) - 40,
			title_size * 2);
		dc.DrawText(
			wxString::Format("%d", strategy_[1][0].second),
			(((size.GetWidth() - title_size) / 2) + title_size) - 40,
			((size.GetHeight() - title_size) / 2) + title_size * 2);
		dc.DrawText(
			wxString::Format("%d", strategy_[1][1].second),
			(size.GetWidth() - border) - 40,
			((size.GetHeight() - title_size) / 2) + title_size * 2);

		// Vertical
		dc.DrawLine(border, border, border, size.GetHeight() - border);
		dc.DrawLine(border + title_size, border, border + title_size, size.GetHeight() - border);
		dc.DrawLine(
			((size.GetWidth() - title_size) / 2) + title_size,
			border,
			((size.GetWidth() - title_size) / 2) + title_size,
			size.GetHeight() - border);
		dc.DrawLine(size.GetWidth() - border, border, size.GetWidth() - border, size.GetHeight() - border);

		// Horizontal
		dc.DrawLine(border, border, size.GetWidth() - border, border);
		dc.DrawLine(border, title_size, size.GetWidth() - border, title_size);
		dc.DrawLine(
			border,
			((size.GetHeight() - title_size) / 2) + title_size,
			size.GetWidth() - border,
			((size.GetHeight() - title_size) / 2) + title_size);
		dc.DrawLine(border, size.GetHeight() - border, size.GetWidth() - border, size.GetHeight() - border);

		// Diagonal
		dc.DrawLine(border + title_size, title_size, size.GetWidth() - border, size.GetHeight() - border);
		dc.DrawLine(
			border + title_size,
			((size.GetHeight() - title_size) / 2) + title_size,
			((size.GetWidth() - title_size) / 2) + title_size,
			size.GetHeight() - border);
		dc.DrawLine(
			((size.GetWidth() - title_size) / 2) + title_size,
			title_size,
			size.GetWidth() - border,
			((size.GetHeight() - title_size) / 2) + title_size);
	}

	void OnSize(wxSizeEvent& e) {
		Refresh();
		e.Skip();
	}

	wxDECLARE_EVENT_TABLE();

	// Private data members
private:
	std::vector<std::vector<std::pair<int, int>>> strategy_;
	std::string select_;
};

wxBEGIN_EVENT_TABLE(GameGrid, wxPanel)
	EVT_PAINT(GameGrid::OnPaint)
	EVT_SIZE(GameGrid::OnSize)
wxEND_EVENT_TABLE()

wxBEGIN_EVENT_TABLE(GameFramePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, GameFramePanel::OnControl)
wxEND_EVENT_TABLE()

GameFramePanel::GameFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
	, palyer1Text_(nullptr)
	, palyer2Text_(nullptr)
	, player1Score_(0)
	, player2Score_(0)
	, random_engine_(static_cast<unsigned int>(std::time(nullptr)))
{

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int borderSize = 2;

	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, GameEvent::ID_PEACE, CONFLICT_PEACE), 1, wxEXPAND);
	controlSizer->Add(new wxButton(this, GameEvent::ID_AGGRESSION, CONFLICT_AGGRESION), 1, wxEXPAND);
	controlSizer->Add(new wxButton(this, GameEvent::ID_OPTIMAL_STRATEGY, CONFLICT_OPTIMAL), 1, wxEXPAND);
	palyer1Text_ = new wxStaticText(this, wxID_ANY, wxString::Format(PLAYER1_SCORE_STUB, player1Score_));
	controlSizer->Add(palyer1Text_, 1, wxEXPAND);
	palyer2Text_ = new wxStaticText(this, wxID_ANY, wxString::Format(PLAYER2_SCORE_STUB, player1Score_));
	controlSizer->Add(palyer2Text_, 1, wxEXPAND);

	topSizer->Add(controlSizer, 0, wxEXPAND | wxLEFT | wxUP | wxDOWN, borderSize);

	// Game grid
	wxBoxSizer* gameGridSizer = new wxBoxSizer(wxHORIZONTAL);
	gameGrid_ = new GameGrid(this);
	gameGridSizer->Add(gameGrid_, 1, wxEXPAND);

	topSizer->Add(gameGridSizer, 1, wxEXPAND);

	SetSizer(topSizer);
}

void GameFramePanel::OnControl(wxCommandEvent& e) {
	const GameEvent buttonId = static_cast<GameEvent>(e.GetId());

	std::uniform_int_distribution<int> distribution(0, 1);
	int player2_choice = distribution(random_engine_);

	if (buttonId == GameEvent::ID_PEACE) {
		auto res = gameGrid_->DoGame(GameEvent::ID_PEACE, player2_choice);

		player1Score_ += res.first;
		palyer1Text_->SetLabel(wxString::Format(PLAYER1_SCORE_STUB, player1Score_));
		player2Score_ += res.second;
		palyer2Text_->SetLabel(wxString::Format(PLAYER2_SCORE_STUB, player2Score_));
	}
	else if (buttonId == GameEvent::ID_AGGRESSION) {
		auto res = gameGrid_->DoGame(GameEvent::ID_AGGRESSION, player2_choice);

		player1Score_ += res.first;
		palyer1Text_->SetLabel(wxString::Format(PLAYER1_SCORE_STUB, player1Score_));
		player2Score_ += res.second;
		palyer2Text_->SetLabel(wxString::Format(PLAYER2_SCORE_STUB, player2Score_));
	}
	else if (buttonId == GameEvent::ID_OPTIMAL_STRATEGY) {
		gameGrid_->DoOptimal();
	}
}

} // namespace game
