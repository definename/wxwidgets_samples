#pragma once

namespace project
{

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

wxDECLARE_APP(ProjectApp);

}; // namespace project