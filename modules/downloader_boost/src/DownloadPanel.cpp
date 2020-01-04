#include "pch.h"
#include "DownloadPanel.h"

namespace downloader
{

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

void DownloadPanel::Completed(const wxString& lable)
{
	activityInd_->Stop();
	text_->SetLabel(lable);
}

boost::signals2::connection DownloadPanel::DoOnCancelSignal(const OnCancelSignal::slot_type& signal)
{
	return onCancel_.connect(signal);
}

void DownloadPanel::Error()
{
	activityInd_->Stop();
	text_->SetLabel(wxT("Error occured"));
}

void DownloadPanel::OnCancel(wxCommandEvent& WXUNUSED(e))
{
	activityInd_->Stop();
	text_->SetLabel(wxT("Downloading operation has been cancelled."));
	onCancel_();
}

void DownloadPanel::Started()
{
	activityInd_->Start();
	text_->SetLabel(wxT("Downloading... Please wait."));
}

} // namespace downloader