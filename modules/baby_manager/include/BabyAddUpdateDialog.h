#pragma once

#include "BabyTypes.h"

namespace baby
{

// Forward declaration.
class BabyAddUpdatePanel;

class BabyAddUpdateDialog: public wxDialog
{
	// Construction and destruction.
public:
	// Constructor.
	BabyAddUpdateDialog(wxWindow* parent, const wxString& title, const BabyDataPtr data = nullptr);
	// Destructor.
	~BabyAddUpdateDialog() = default;

	// Public interface.
public:
	// Get data.
	BabyDataPtr GetBabyData() const;

	// Public types.
public:
	// Add panel pointer type.
	using BabyAddPanelPtr = BabyAddUpdatePanel*;

	// Private members.
private:
	// Panel pointer.
	BabyAddPanelPtr addUpdatePanel_;
};

};