#include "pch.h"
#include "ProjectApp.h"
#include "DownloadFrame.h"

namespace downloader
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(ProjectApp);

ProjectApp::ProjectApp()
	: isSilentMode_(false)
	, isUpdateMode_(false)
	, isNoTrayMode_(false)
{ }

ProjectApp::~ProjectApp()
{ }

bool ProjectApp::IsNoTrayMode() const
{
	return isNoTrayMode_;
}

bool ProjectApp::IsSilentMode() const
{
	return isSilentMode_;
}

bool ProjectApp::IsUpdateMode() const
{
	return isUpdateMode_;
}

bool ProjectApp::OnInit(void)
{
	if (!wxApp::OnInit())
		return false;

	DownloadFrame* downloaderFrame_;
	downloaderFrame_ = new DownloadFrame();

	if (!isSilentMode_)
		downloaderFrame_->Show(true);

	downloaderFrame_->StartDownloading();
	
	return true;
}

bool ProjectApp::OnCmdLineParsed(wxCmdLineParser& parser)
{
	isSilentMode_ = parser.Found(wxT("s"));
	isUpdateMode_ = parser.Found(wxT("u"));
	isNoTrayMode_ = parser.Found(wxT("nt"));

	return true;
}

void ProjectApp::OnInitCmdLine(wxCmdLineParser& parser)
{
	parser.SetDesc(cmdLineDesc);
	parser.SetSwitchChars(wxT("-"));
}

} // namespace downloader
