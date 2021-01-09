#pragma once

namespace game
{

class GameFramePanel : public wxPanel
{
	// Construction and destruction.
public:
	// Constructor.
	GameFramePanel(wxWindow* parent);
	// Destructor.
	~GameFramePanel() = default;

	// Public interface.
public:
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();
};

}; // namespace game