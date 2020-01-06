#include "pch.h"
#include "ZooFrame.h"
#include "ZooListPanel.h"

namespace zoo
{

ZooFrame::ZooFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Zoo Manager"), wxDefaultPosition, wxSize(850, 300), wxDEFAULT_FRAME_STYLE)
	, zooPanel_(new ZooListPanel(this))
{
	SetMinSize(GetSize());
}

ZooFrame::~ZooFrame() {
}

} // namespace zoo
