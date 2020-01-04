#include "pch.h"
#include "NullFrame.h"
#include "SoftPanel.h"

namespace soft
{

//! Event table.
wxBEGIN_EVENT_TABLE(NullFrame, wxFrame)
	EVT_CLOSE(NullFrame::OnCloseWindow)
wxEND_EVENT_TABLE()

NullFrame::NullFrame()
	: wxFrame(NULL, wxID_ANY, wxT("NULL FRAME"), wxDefaultPosition, wxSize(850, 300), wxDEFAULT_FRAME_STYLE)
	, softPanel_(new SoftPanel(this))
{
	SetIcon(wxICON(IDI_ICON));
	SetMinSize(GetSize());
}

NullFrame::~NullFrame()
{ }

void NullFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e))
{
	Destroy();
}

}
