#include "pch.h"
#include "ProjectApp.h"
#include "DownloadFrame.h"

namespace downloader
{

//! Macro will allow wxWidgets to create the application object during program execution.
IMPLEMENT_APP(ProjectApp)

//! Constructor.
ProjectApp::ProjectApp()
{ }

ProjectApp::~ProjectApp()
{ }

bool ProjectApp::OnInit(void)
{
	if (!wxApp::OnInit())
		return false;

	DownloadFrame* downloaderFrame_;
	downloaderFrame_ = new DownloadFrame();
	downloaderFrame_->Show(true);
	downloaderFrame_->Start();

	return true;
}

} // namespace downloader
