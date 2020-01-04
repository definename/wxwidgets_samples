#pragma once

namespace null_app
{

//! Forward declaration.
class NullPanel;

class NullFrame : public wxFrame
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	NullFrame();
	//! destructor.
	~NullFrame();

	//
	// Public types.
	//
public:
	//! Panel pointer type.
	typedef NullPanel* NullPanelPtr;

	//
	// Private interface.
	//
private:
	//! On close event handler.
	void NullFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e));
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! panel pointer.
	NullPanelPtr nullPanel_;
};

}; // namespace null_app