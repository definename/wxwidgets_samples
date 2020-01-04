#pragma once

namespace soft
{

//! Forward declaration.
class NullFrame;

class NullApp : public wxApp
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	NullApp();
	//! destructor.
	~NullApp();

	//
	// Public types.
	//
public:
	//! Main frame pointer type.
	typedef NullFrame* NullFramePtr;

	//
	// Public interface.
	//
public:
	//! For any processing which needs to be done as the application is about to exit.
	virtual int OnExit();
	//! Initializes the application.
	virtual bool OnInit(void);

	//
	// Private date members.
	//
private:
	//! Null frame pointer.
	NullFramePtr nullFrame_;
};

wxDECLARE_APP(NullApp);

};