#include "pch.h"
#include "SoftPanel.h"
#include "SoftListCtrl.h"
#include "SoftScanner.h"

namespace soft
{

wxBEGIN_EVENT_TABLE(SoftPanel, wxPanel)
wxEND_EVENT_TABLE()

SoftPanel::SoftPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	InitializePanel(topSizer);
	SetSizer(topSizer);

	//! Todo. Do this in separate thread.
	scanner_->Scan();

	size_t size = scanner_->GetScanResult()->size();
	softList_->SetItemCount(scanner_->GetScanResult()->size());

	wxMessageBox(wxString::Format("I Have found %i applications", size), wxT("Total"), wxICON_INFORMATION);
}

SoftPanel::~SoftPanel()
{ }

void SoftPanel::InitializePanel(wxBoxSizer* sizer)
{
	wxBoxSizer* listSizer = new wxBoxSizer(wxHORIZONTAL);

	scanner_ = new SoftScanner();
	softList_ = new SoftListCtrl(this, scanner_);
	listSizer->Add(softList_, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 0));

	sizer->Add(listSizer, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 0));
}

}
