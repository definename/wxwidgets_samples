#pragma once

namespace game
{

//! Forward declaration.
class GameFrame;

class GameApp : public wxApp
{
	// Construction and destruction.
public:
	// Constructor.
	GameApp() = default;
	// Destructor.
	~GameApp() = default;

	// Public types.
public:
	// Main frame pointer type.
	using GameFramePtr = GameFrame*;

	//
	// Public interface.
	//
public:
	// For any processing which needs to be done as the application is about to exit.
	virtual int OnExit() wxOVERRIDE;
	// Initializes the application.
	virtual bool OnInit(void) wxOVERRIDE;

	//
	// Private date members.
	//
private:
	// Game frame pointer.
	GameFramePtr zooFrame_;
};

wxDECLARE_APP(GameApp);

}; // namespace game