#include "pch.h"
#include "NullFrame.h"
#include "NullPanel.h"

namespace null_app
{

//! Event table.
wxBEGIN_EVENT_TABLE(NullFrame, wxFrame)
	EVT_CLOSE(NullFrame::OnCloseWindow)
wxEND_EVENT_TABLE()

NullFrame::NullFrame()
	: wxFrame(
	NULL,
	wxID_ANY,
	wxT("NULL FRAME"),
	wxDefaultPosition,
	wxSize(wxDisplay().GetGeometry().GetWidth() / 2, wxDisplay().GetGeometry().GetHeight() / 2),
	wxNO_BORDER)
	, nullPanel_(new NullPanel(this))
{
	this->SetIcon(wxICON(IDI_ICON));
	this->SetBackgroundColour(wxColor(255, 255, 255));
}

NullFrame::~NullFrame()
{ }

void NullFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e))
{
	Destroy();
}

} // namespace null_app
