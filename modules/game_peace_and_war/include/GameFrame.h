#pragma once

namespace game
{

// Forward declaration.
class GameFramePanel;

class GameFrame: public wxFrame
{
	// Construction and destruction.
public:
	// Constructor.
	GameFrame();
	// Destructor.
	~GameFrame() = default;

	// Public types.
public:
	// Frame panel pointer type.
	using GamePanelPtr = GameFramePanel*;

	// Private members.
private:
	// Game panel pointer.
	GamePanelPtr gamePanel_;
};

}; // namespace game