#pragma once

namespace greedy
{

// Forward declaration.
class GreedyFramePanel;

class GreedyFrame: public wxFrame
{
	// Construction and destruction.
public:
	// Constructor.
	GreedyFrame();
	// Destructor.
	~GreedyFrame() = default;

	// Public types.
public:
	// Frame panel pointer type.
	using GreedyPanelPtr = GreedyFramePanel*;

	// Private members.
private:
	// Frame panel pointer.
	GreedyPanelPtr framePanel_;
};

}; // namespace greedy