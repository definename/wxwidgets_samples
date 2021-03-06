#pragma once

namespace zoo
{

// Forward declaration.
class ZooFramePanel;

class ZooFrame: public wxFrame
{
	// Construction and destruction.
public:
	// Constructor.
	ZooFrame();
	// Destructor.
	~ZooFrame() = default;

	// Public types.
public:
	// Frame panel pointer type.
	using ZooPanelPtr = ZooFramePanel*;

	// Private interface.
private:
	// Menu event handler.
	void OnMenuEvent(wxCommandEvent& e);

	// Private members.
private:
	// Zoo panel pointer.
	ZooPanelPtr zooPanel_;
};

}; // namespace zoo