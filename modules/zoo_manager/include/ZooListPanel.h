#pragma once

namespace zoo
{

// Forward declaration.
class ZooList;

class ZooListPanel : public wxPanel
{
	// Construction and destruction.
public:
	//! Constructor.
	ZooListPanel(wxWindow* parent);
	//! Destructor.
	~ZooListPanel();

	// Public types.
public:
	//! Main frame pointer type.
	using ZooListPtr = ZooList*;
	//! Command id type.
	enum class CommandId : int
	{
		ID_ADD = 0,
		ID_REMOVE,
		ID_UPDATE
	};

	// Private interface
private:
	// Control event handler.
	void OnControl(wxCommandEvent& e);
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	// Private members.
private:
	ZooListPtr zooList_;
};

}; // namespace zoo