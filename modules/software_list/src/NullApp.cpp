#include "pch.h"
#include "NullApp.h"
#include "NullFrame.h"

namespace soft
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(NullApp);

NullApp::NullApp()
{ }

NullApp::~NullApp()
{ }

int NullApp::OnExit()
{
	return wxApp::OnExit();
}

bool NullApp::OnInit(void)
{
	if (!wxApp::OnInit())
		return false;

	nullFrame_ = new NullFrame();
	nullFrame_->Show(true);

	return true;
}

} // namespace null_app
