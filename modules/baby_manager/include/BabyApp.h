#pragma once

namespace baby
{

//! Forward declaration.
class BabyFrame;

class BabyApp : public wxApp
{
	// Construction and destruction.
public:
	// Constructor.
	BabyApp() = default;
	// Destructor.
	~BabyApp() = default;

	// Public types.
public:
	// Main frame pointer type.
	using BabyFramePtr = BabyFrame*;

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
	// Zoo frame pointer.
	BabyFramePtr frame_;
};

wxDECLARE_APP(BabyApp);

};