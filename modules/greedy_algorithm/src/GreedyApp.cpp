#include "pch.h"
#include "GreedyApp.h"
#include "GreedyFrame.h"

namespace greedy
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(GreedyApp);

int GreedyApp::OnExit() {
	return wxApp::OnExit();
}

bool GreedyApp::OnInit(void) {
	if (!wxApp::OnInit()) {
		return false;
	}

	appFrame_ = new GreedyFrame();
	return appFrame_->Show(true);
}

} // namespace greedy
