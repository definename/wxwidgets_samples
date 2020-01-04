#pragma once

namespace ftp
{

class TextControl : public wxTextCtrl
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	TextControl(wxWindow* parent, const long& style = wxTE_LEFT);
	//! Destructor.
	~TextControl();

	//
	// Public types.
	//
public:

	//
	// Public interface.
	//
public:

	//
	// Private interface.
	//
private:
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:

};

}; // namespace null_app