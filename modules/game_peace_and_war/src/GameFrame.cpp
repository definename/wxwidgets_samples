#include "pch.h"
#include "GameFrame.h"
#include "GameFramePanel.h"

namespace game
{

GameFrame::GameFrame()
	: wxFrame(NULL, wxID_ANY, wxT("GameApp"), wxDefaultPosition, wxSize(550, 300), wxDEFAULT_FRAME_STYLE)
	, gamePanel_(new GameFramePanel(this)) {
	SetIcon(wxICON(IDI_ICON));
	SetMinSize(GetSize());
}

} // namespace game
