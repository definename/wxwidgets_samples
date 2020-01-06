#pragma once

namespace zoo
{

// Forward declaration.
class ZooListPanel;

class ZooFrame: public wxFrame
{
	// Construction and destruction.
public:
	//! Constructor.
	ZooFrame();
	//! Destructor.
	~ZooFrame();

	// Public types.
public:
	//! Main frame pointer type.
	using ZooPanelPtr = ZooListPanel*;

	// Private members.
private:
	ZooPanelPtr zooPanel_;
};

}; // namespace zoo