#pragma once

namespace null_app
{

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
	// Private interface.
	//
private:
	//! On close event handler.
	void NullFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e));
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();
};

};