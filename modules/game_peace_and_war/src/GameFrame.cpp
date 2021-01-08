#include "pch.h"
#include "GameFrame.h"

namespace game
{

GameFrame::GameFrame()
	: wxFrame(NULL, wxID_ANY, wxT("GameApp"), wxDefaultPosition, wxSize(550, 300), wxDEFAULT_FRAME_STYLE)
{
	SetIcon(wxICON(IDI_ICON));
	SetMinSize(GetSize());
}

} // namespace game
