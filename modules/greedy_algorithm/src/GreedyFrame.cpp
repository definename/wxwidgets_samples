#include "pch.h"
#include "GreedyFrame.h"
#include "GreedyFramePanel.h"

namespace greedy
{

GreedyFrame::GreedyFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Greedy algorithm"), wxDefaultPosition, wxSize(550, 400), wxDEFAULT_FRAME_STYLE)
	, framePanel_(new GreedyFramePanel(this)) {
	SetIcon(wxICON(IDI_ICON));
	SetMinSize(GetSize());
}

} // namespace greedy
