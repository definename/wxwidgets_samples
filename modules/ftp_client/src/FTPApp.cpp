#include "pch.h"
#include "FTPApp.h"
#include "FTPFrame.h"

namespace ftp
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(FTPApp);

FTPApp::FTPApp()
{ }

FTPApp::~FTPApp()
{ }

int FTPApp::OnExit()
{
	return wxApp::OnExit();
}

bool FTPApp::OnInit(void)
{
	if (!wxApp::OnInit())
		return false;

	wxImage::AddHandler(new wxPNGHandler);

	ftpFrame_ = new FTPFrame();
	ftpFrame_->Show(true);

	return true;
}

} // namespace null_app
