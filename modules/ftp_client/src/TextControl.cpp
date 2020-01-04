#include "pch.h"
#include "TextControl.h"

namespace ftp
{

wxBEGIN_EVENT_TABLE(TextControl, wxTextCtrl)
wxEND_EVENT_TABLE()

TextControl::TextControl(wxWindow* parent, const long& style /*= wxTE_LEFT */)
	: wxTextCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, style)
{ }

TextControl::~TextControl()
{ }

} // namespace null_app
