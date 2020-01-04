#pragma once

namespace null_app
{

class NullPanel : public wxPanel
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	NullPanel(wxWindow* parent);
	//! destructor.
	~NullPanel();

	//
	// Public types.
	//
public:
	//! Web view pointer type.
	typedef wxWebView* NullWebViewPtr;

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
	//! Web view pointer.
	NullWebViewPtr nullWebView_;
	//! Web page.
	std::string page_;
};

}; // namespace null_app