#include "pch.h"
#include "NullFrame.h"

namespace null_app
{

//! Event table.
wxBEGIN_EVENT_TABLE(NullFrame, wxFrame)
	EVT_CLOSE(NullFrame::OnCloseWindow)
wxEND_EVENT_TABLE()

NullFrame::NullFrame()
	: wxFrame(NULL, wxID_ANY, wxT("NULL FRAME"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE)
{
	SetIcon(wxICON(IDI_ICON));
}

NullFrame::~NullFrame()
{ }

void NullFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e))
{
	Destroy();
}

}
