#pragma once

namespace zoo
{

// Forward declaration.
class ZooAddPanel;

class ZooAddDialog: public wxDialog
{
	// Construction and destruction.
public:
	//! Constructor.
	ZooAddDialog(wxWindow* parent);
	//! Destructor.
	~ZooAddDialog();

	// Public types.
public:
	//! Add panel pointer type.
	using ZooAddPanelPtr = ZooAddPanel*;

	// Private members.
private:
	//! Add panel pointer.
	ZooAddPanelPtr zooAddPanel_;
};

}; // namespace zoo