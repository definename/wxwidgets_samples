#pragma once

#include "Types.h"

namespace soft
{

class SoftPanel : public wxPanel
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	SoftPanel(wxWindow* parent);
	//! Destructor.
	~SoftPanel();

	//
	// Private interface.
	//
private:
	//! Initializes buttons.
	void InitializePanel(wxBoxSizer* sizer);
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! Software list ctrl.
	SoftListCtrlPtr softList_;
	//! Scanner.
	SoftScannerPtr scanner_;
};

};