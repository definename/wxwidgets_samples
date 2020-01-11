#pragma once

#include "ZooTypes.h"

namespace zoo
{

// Forward declaration.
class ZooAddUpdatePanel;

class ZooAddUpdateDialog: public wxDialog
{
	// Construction and destruction.
public:
	// Constructor.
	ZooAddUpdateDialog(wxWindow* parent, const wxString& title, const ZooDataPtr zooData = nullptr);
	// Destructor.
	~ZooAddUpdateDialog();

	// Public interface.
public:
	// Get zoo data.
	ZooDataPtr GetZooData() const;

	// Public types.
public:
	// Add panel pointer type.
	using ZooAddPanelPtr = ZooAddUpdatePanel*;

	// Private members.
private:
	// Panel pointer.
	ZooAddPanelPtr zooAddUpdatePanel_;
};

}; // namespace zoo