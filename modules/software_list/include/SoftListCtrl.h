#pragma once

#include "Types.h"

namespace soft
{

class SoftListCtrl : public wxListCtrl
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	SoftListCtrl(wxWindow* parent, SoftScannerPtr scanner);
	//! Destructor.
	~SoftListCtrl();

	//
	// Private interface.
	//
private:
	//! It returns the string containing the text of the given column for the specified item.
	virtual wxString OnGetItemText(long item, long column) const;
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! Scanner pointer.
	SoftScannerPtr scanner_;
};

};