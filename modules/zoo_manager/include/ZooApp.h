#pragma once

namespace zoo
{

//! Forward declaration.
class ZooFrame;

class ZooApp : public wxApp
{
	// Construction and destruction.
public:
	//! Constructor.
	ZooApp() = default;
	//! Destructor.
	~ZooApp() = default;

	// Public types.
public:
	//! Main frame pointer type.
	using ZooFramePtr = ZooFrame*;

	//
	// Public interface.
	//
public:
	//! For any processing which needs to be done as the application is about to exit.
	virtual int OnExit() wxOVERRIDE;
	//! Initializes the application.
	virtual bool OnInit(void) wxOVERRIDE;

	//
	// Private date members.
	//
private:
	//! Main frame pointer.
	ZooFramePtr zooFrame_;
};

wxDECLARE_APP(ZooApp);

}; // namespace zoo