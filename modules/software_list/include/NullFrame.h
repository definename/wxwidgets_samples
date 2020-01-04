#pragma once

namespace soft
{

//! Forward declaration.
class SoftPanel;

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
	typedef SoftPanel* SoftPanelPtr;

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
	//! Software panel.
	SoftPanelPtr softPanel_;
};

};