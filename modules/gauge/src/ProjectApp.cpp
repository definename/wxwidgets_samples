#include "pch.h"
#include "ProjectApp.h"
#include "ProjectFrame.h"

namespace project
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(ProjectApp);

ProjectApp::ProjectApp()
{ }

ProjectApp::~ProjectApp()
{ }

bool ProjectApp::OnInit(void)
{
	if (!wxApp::OnInit())
		return false;

	ProjectFrame* frame = new ProjectFrame();
	frame->Show();

	return true;
}

} // namespace project
