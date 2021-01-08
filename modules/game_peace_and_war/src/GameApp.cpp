#include "pch.h"
#include "GameApp.h"
#include "GameFrame.h"

namespace game
{

//! Macro will allow wxWidgets to create the application object during program execution.
wxIMPLEMENT_APP(GameApp);

int GameApp::OnExit() {
	return wxApp::OnExit();
}

bool GameApp::OnInit(void) {
	if (!wxApp::OnInit()) {
		return false;
	}

	zooFrame_ = new GameFrame();
	return zooFrame_->Show(true);
}

} // namespace zoo
