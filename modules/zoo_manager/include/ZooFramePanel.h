#pragma once

namespace zoo
{

// Forward declaration.
class ZooList;

class ZooFramePanel : public wxPanel
{
	// Construction and destruction.
public:
	// Constructor.
	ZooFramePanel(wxWindow* parent);
	// Destructor.
	~ZooFramePanel();

	// Public types.
public:
	// Frame pointer type.
	using ZooListPtr = ZooList*;

	// Public interface.
public:
	// Control event handler.
	void OnControl(wxCommandEvent& e);
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	// Private members.
private:
	// Gui list control pointer.
	ZooListPtr zooList_;
};

}; // namespace zoo