#pragma once

namespace ftp
{

//! Forward declaration.
class FTPFrame;

class FTPApp : public wxApp
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	FTPApp();
	//! destructor.
	~FTPApp();

	//
	// Public types.
	//
public:
	//! Main frame pointer type.
	typedef FTPFrame* FTPFramePtr;

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
	//! FTP frame pointer.
	FTPFramePtr ftpFrame_;
};

wxDECLARE_APP(FTPApp);

}; // namespace null_app