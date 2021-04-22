#pragma once

namespace baby
{

// Forward declaration.
class BabyFramePanel;

class BabyFrame: public wxFrame
{
	// Construction and destruction.
public:
	// Constructor.
	BabyFrame();
	// Destructor.
	~BabyFrame() = default;

	// Public types.
public:
	// Frame panel pointer type.
	using BabyPanelPtr = BabyFramePanel*;

	// Private interface.
private:
	// Menu event handler.
	void OnMenuEvent(wxCommandEvent& e);
	// On close event handler
	void OnClose(wxCloseEvent& e);

	// Private members.
private:
	// Panel pointer.
	BabyPanelPtr panel_;
};

};