#pragma once

namespace greedy
{

// Forward declaration.
class GreedyGrid;

class GreedyFramePanel : public wxPanel
{
	// Construction and destruction.
public:
	// Constructor.
	GreedyFramePanel(wxWindow* parent);
	// Destructor.
	~GreedyFramePanel() = default;

private:
	// Private interface
	void OnControl(wxCommandEvent& e);

private:
	GreedyGrid* grid_;

	// Public interface.
public:
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();
};

}; // namespace greedy