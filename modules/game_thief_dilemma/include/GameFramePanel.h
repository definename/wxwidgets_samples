#pragma once

namespace game
{

// Forward declaration.
class GameGrid;

class GameFramePanel : public wxPanel
{
	// Construction and destruction.
public:
	// Constructor.
	GameFramePanel(wxWindow* parent);
	// Destructor.
	~GameFramePanel() = default;

private:
	// Private interface
	void OnControl(wxCommandEvent& e);

private:
	wxStaticText* palyer1Text_;
	wxStaticText* palyer2Text_;
	int player1Score_;
	int player2Score_;
	wxGrid* grid_;
	std::default_random_engine random_engine_;
	GameGrid* gameGrid_;

	// Public interface.
public:
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();
};

}; // namespace game