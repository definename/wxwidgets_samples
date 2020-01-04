#pragma once

namespace ftp
{

class SplitterWindow : public wxSplitterWindow
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	SplitterWindow(wxWindow* parent);
	//! Destructor.
	~SplitterWindow();

	//
	// Public interface.
	//
public:
	//! On double click event handler.
	void OnDClick(wxSplitterEvent& e);
	//! On position changed event handler.
	void OnPositionChanged(wxSplitterEvent& e);
	//! On position changing event handler.
	void OnPositionChanging(wxSplitterEvent& e);
	//! On unsplit event handler.
	void OnUnsplitEvent(wxSplitterEvent& e);

	//
	// Private interface.
	//
private:
	//! Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();
	//! Disables the generation of default copy ctor and assignment operator.
	wxDECLARE_NO_COPY_CLASS(SplitterWindow);
};

}; // namespace null_app