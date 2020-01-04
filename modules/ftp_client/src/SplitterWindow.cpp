#include "pch.h"
#include "SplitterWindow.h"

namespace ftp
{

wxBEGIN_EVENT_TABLE(SplitterWindow, wxSplitterWindow)
	EVT_SPLITTER_SASH_POS_CHANGED(wxID_ANY, SplitterWindow::OnPositionChanged)
	EVT_SPLITTER_SASH_POS_CHANGING(wxID_ANY, SplitterWindow::OnPositionChanging)
	EVT_SPLITTER_DCLICK(wxID_ANY, SplitterWindow::OnDClick)
	EVT_SPLITTER_UNSPLIT(wxID_ANY, SplitterWindow::OnUnsplitEvent)
wxEND_EVENT_TABLE()

SplitterWindow::SplitterWindow(wxWindow* parent)
	: wxSplitterWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D | wxSP_LIVE_UPDATE | wxCLIP_CHILDREN)
{ }

SplitterWindow::~SplitterWindow()
{ }

void SplitterWindow::OnDClick(wxSplitterEvent& e)
{
	wxSplitMode mode(GetSplitMode());
	if (mode == wxSPLIT_VERTICAL)
		SetSashPosition(GetSize().GetWidth() / 2);
	else if (mode == wxSPLIT_HORIZONTAL)
		SetSashPosition((GetSize().GetHeight() / 10) * 8);

	e.Veto();
}

void SplitterWindow::OnPositionChanged(wxSplitterEvent& e)
{
	e.Skip();
}

void SplitterWindow::OnPositionChanging(wxSplitterEvent& e)
{
	e.Skip();
}

void SplitterWindow::OnUnsplitEvent(wxSplitterEvent& e)
{
	e.Skip();
}

} // namespace null_app