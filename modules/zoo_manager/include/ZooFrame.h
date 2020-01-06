#pragma once

namespace zoo
{

// Forward declaration.
class ZooFramePanel;

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
	using ZooPanelPtr = ZooFramePanel*;

	// Private members.
private:
	ZooPanelPtr zooPanel_;
};

}; // namespace zoo