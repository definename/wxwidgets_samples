#pragma once

namespace greedy
{

//! Forward declaration.
class GreedyFrame;

class GreedyApp : public wxApp
{
	// Construction and destruction.
public:
	// Constructor.
	GreedyApp() = default;
	// Destructor.
	~GreedyApp() = default;

	// Public types.
public:
	// Main frame pointer type.
	using AppFramePtr = GreedyFrame *;

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
	// App frame pointer.
	AppFramePtr appFrame_;
};

wxDECLARE_APP(GreedyApp);

}; // namespace greedy