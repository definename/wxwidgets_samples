#include "pch.h"
#include "GameFramePanel.h"

namespace game
{

wxBEGIN_EVENT_TABLE(GameFramePanel, wxPanel)
/*	EVT_BUTTON(wxID_ANY, ZooFramePanel::OnControl)*/
wxEND_EVENT_TABLE()

GameFramePanel::GameFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize()) {
}

} // namespace game
