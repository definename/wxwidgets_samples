#pragma once

namespace baby
{

// Forward declaration.
class BabyList;

class BabyFramePanel : public wxPanel
{
	// Construction and destruction.
public:
	// Constructor.
	BabyFramePanel(wxWindow* parent);
	// Destructor.
	~BabyFramePanel() = default;

	// Public types.
public:
	// Frame pointer type.
	using BabyListPtr = BabyList*;

	// Public interface.
public:
	// Control event handler.
	void OnControl(wxCommandEvent& e);

	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	// Private members.
private:
	// Gui list control pointer.
	BabyListPtr list_;
};

};