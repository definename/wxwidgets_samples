#include "pch.h"
#include "ZooFrame.h"
#include "ZooFramePanel.h"

namespace zoo
{

ZooFrame::ZooFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Zoo Manager"), wxDefaultPosition, wxSize(550, 300), wxDEFAULT_FRAME_STYLE)
	, zooPanel_(new ZooFramePanel(this))
{
	SetMinSize(GetSize());
}

ZooFrame::~ZooFrame() {
}

} // namespace zoo
