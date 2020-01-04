#pragma once

namespace downloader
{

//! Forward declaration.
class DownloadFrame;

class ProjectApp : public wxApp
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	ProjectApp();
	//! destructor.
	~ProjectApp();

	//
	// Public interface.
	//
public:
	//! Initializes the application.
	virtual bool OnInit(void);
};

} // namespace downloader