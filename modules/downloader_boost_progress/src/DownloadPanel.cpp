#include "pch.h"
#include "DownloadPanel.h"

namespace downloader
{

BEGIN_EVENT_TABLE(DownloadPanel, wxPanel)
END_EVENT_TABLE()

DownloadPanel::DownloadPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize)
	, activityInd_(new wxActivityIndicator(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, wxT("Progress")))
	, activitySizer_(new wxBoxSizer(wxHORIZONTAL))
	, gauge_(new wxGauge(this, wxID_ANY, MAXRANGE, wxDefaultPosition, wxDefaultSize, wxGA_HORIZONTAL | wxGA_PROGRESS))
	, gaugeSizer_(new wxBoxSizer(wxVERTICAL))
	, textGauge_(new wxStaticText(this, wxID_ANY, wxT("Downloading... Please wait."), wxDefaultPosition, wxDefaultSize))
	, topSizer_(new wxBoxSizer(wxHORIZONTAL))
	, textVersion_(new wxStaticText(this, wxID_ANY, wxT("Connection to the server..."), wxDefaultPosition, wxDefaultSize))
{
	activityInd_->Start();
	activitySizer_->Add(activityInd_, wxSizerFlags().Proportion(0).Border(wxLEFT, 10).Center());
	activitySizer_->Add(textVersion_, wxSizerFlags().Proportion(0).Border(wxALL, 10).Center());
	activitySizer_->Show(true);

	gaugeSizer_->Add(textGauge_, wxSizerFlags().Proportion(1).Expand().Border(wxLEFT | wxRIGHT, 10));
	gaugeSizer_->Add(gauge_, wxSizerFlags().Proportion(1).Expand().Border(wxLEFT | wxRIGHT, 10));
	gaugeSizer_->Show(false);

	topSizer_->Add(activitySizer_, wxSizerFlags().Proportion(1).Center());
	topSizer_->Add(gaugeSizer_, wxSizerFlags().Proportion(1).Center());

	SetSizer(topSizer_);
}

DownloadPanel::~DownloadPanel()
{ }

void DownloadPanel::DownloadedFileVersion(const wxString& lable)
{
	activityInd_->Stop();
	textVersion_->SetLabel(lable);
}

void DownloadPanel::DownloadedInstaller(const wxString& lable)
{
	gauge_->SetValue(MAXRANGE);
	textGauge_->SetLabel(lable);
}

void DownloadPanel::Error()
{
	if (topSizer_->IsShown(activitySizer_))
	{
		activityInd_->Stop();
		textVersion_->SetLabel(wxT("Error occured"));
	}
	else if (topSizer_->IsShown(gaugeSizer_))
	{
		textGauge_->SetLabel(wxT("Error occured"));
	}
}

void DownloadPanel::Progress()
{
	int p = gauge_->GetValue();
	if (gauge_->GetValue() < MAXRANGE)
		gauge_->SetValue(++p);
}

void DownloadPanel::Started()
{
	activitySizer_->Show(false);
	gaugeSizer_->Show(true);
	topSizer_->SetDimension(0, 0, GetSize().GetWidth(), GetSize().GetHeight());
}

} // namespace downloader