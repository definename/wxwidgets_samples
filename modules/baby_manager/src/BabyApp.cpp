#include "pch.h"
#include "BabyApp.h"
#include "BabyFrame.h"

namespace baby
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(BabyApp);

int BabyApp::OnExit() {
	return wxApp::OnExit();
}

bool BabyApp::OnInit(void) {
	if (!wxApp::OnInit()) {
		return false;
	}

	frame_ = new BabyFrame();
	return frame_->Show(true);
}

}
