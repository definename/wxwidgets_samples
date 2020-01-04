#include "pch.h"
#include "NullPanel.h"

namespace null_app
{

//! Event table.
wxBEGIN_EVENT_TABLE(NullPanel, wxPanel)
wxEND_EVENT_TABLE()

NullPanel::NullPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxPoint(2, 2), wxSize(parent->GetSize().GetWidth() - 4, parent->GetSize().GetHeight() - 4), wxNO_BORDER)
	, nullWebView_(wxWebView::New(
		this,
		wxID_ANY,
		"www.google.com",
		wxDefaultPosition,
		wxSize(this->GetSize().GetWidth(), this->GetSize().GetHeight()),
		wxWebViewBackendDefault,
		wxNO_BORDER))
		// by default - wxBORDER_DEFAULT
{
	this->SetBackgroundColour(wxColor(0, 0, 0));
}

NullPanel::~NullPanel()
{ }

} // namespace null_app
