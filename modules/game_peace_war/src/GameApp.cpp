#include "pch.h"
#include "ZooApp.h"
#include "ZooFrame.h"

namespace zoo
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(ZooApp);

int ZooApp::OnExit() {
	return wxApp::OnExit();
}

bool ZooApp::OnInit(void) {
	if (!wxApp::OnInit()) {
		return false;
	}

	zooFrame_ = new ZooFrame();
	return zooFrame_->Show(true);
}

} // namespace zoo
