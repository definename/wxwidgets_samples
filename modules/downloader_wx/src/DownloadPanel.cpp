#include "pch.h"
#include "DownloadPanel.h"

namespace downloader
{

//! Event table.
BEGIN_EVENT_TABLE(DownloadPanel, wxPanel)
END_EVENT_TABLE()

DownloadPanel::DownloadPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
	, activityInd_(new wxActivityIndicator(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("Progress")))
	, downloadBtn_(new wxButton(this, wxID_ANY, wxT("Cancel"), wxDefaultPosition, wxSize(100, 30)))
	, text_(new wxStaticText(this, wxID_ANY, wxT("Connection to the server..."), wxDefaultPosition, wxDefaultSize))
	, topSizer_(new wxBoxSizer(wxHORIZONTAL))
	, activitySizer_(new wxBoxSizer(wxVERTICAL))
	, textSizer_(new wxBoxSizer(wxVERTICAL))
	, btnSizer_(new wxBoxSizer(wxVERTICAL))
{
	activityInd_->Start();
	activitySizer_->Add(activityInd_, wxSizerFlags().Proportion(0).Border(wxLEFT, 10));

	textSizer_->Add(text_, wxSizerFlags().Proportion(1).Border(wxALL, 10));

	downloadBtn_->Bind(wxEVT_BUTTON, &DownloadPanel::OnCancel, this);
	btnSizer_->Add(downloadBtn_, wxSizerFlags().Proportion(0).Border(wxALL, 10).Right());

	topSizer_->Add(activitySizer_, wxSizerFlags().Proportion(0).Center());
	topSizer_->Add(textSizer_, wxSizerFlags().Proportion(1).Center());
	topSizer_->Add(btnSizer_, wxSizerFlags().Proportion(1).Center());

	// 	topSizer_->Fit(this);
	// 	topSizer_->SetSizeHints(this);
	SetSizer(topSizer_);
}

DownloadPanel::~DownloadPanel()
{ }

void DownloadPanel::OnCancel(wxCommandEvent& WXUNUSED(e))
{
	wxMessageBox(wxT("Implement functionality to stop downloding"), wxT("Downloader"), wxOK);
}

} // namespace downloader