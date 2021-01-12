#include "pch.h"
#include "GreedyFramePanel.h"
#include "GreedyTypes.h"

namespace greedy
{

wxBEGIN_EVENT_TABLE(GreedyFramePanel, wxPanel)
	EVT_BUTTON(wxID_ANY, GreedyFramePanel::OnControl)
wxEND_EVENT_TABLE()

GreedyFramePanel::GreedyFramePanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
{

	wxBoxSizer* topSizer = new wxBoxSizer(wxHORIZONTAL);
	const int borderSize = 2;

	// Game grid
// 	wxBoxSizer* gameGridSizer = new wxBoxSizer(wxHORIZONTAL);
// 	gameGrid_ = new GameGrid(this);
// 	gameGridSizer->Add(gameGrid_, 1, wxEXPAND);
// 
// 	topSizer->Add(gameGridSizer, 1, wxEXPAND);

	// Buttons.
	wxBoxSizer* controlSizer = new wxBoxSizer(wxVERTICAL);
	controlSizer->Add(new wxButton(this, GreedyEvent::ID_NEXT, wxT("Next")), 1, wxEXPAND);

	topSizer->Add(controlSizer, 0, wxLEFT | wxUP | wxDOWN, borderSize);

	SetSizer(topSizer);
}

void GreedyFramePanel::OnControl(wxCommandEvent& e) {
	const GreedyEvent buttonId = static_cast<GreedyEvent>(e.GetId());

	if (buttonId == GreedyEvent::ID_NEXT) {
		wxMessageBox(wxT("1"));
	}
}

} // namespace greedy
