#include "pch.h"
#include "DownloadFrame.h"
#include "DownloadPanel.h"
#include "DownloadThread.h"
#include "Installer.h"

namespace downloader
{

wxDEFINE_EVENT(wxEVT_COMMAND_DOWNLOADTHREAD_COMPLETED, wxCommandEvent);
wxDEFINE_EVENT(wxEVT_COMMAND_DOWNLOADTHREAD_ERROR, wxCommandEvent);

//! Event table.
wxBEGIN_EVENT_TABLE(DownloadFrame, wxFrame)
	EVT_CLOSE(DownloadFrame::OnCloseWindow)
	EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_DOWNLOADTHREAD_COMPLETED, DownloadFrame::OnDownloadCompleated)
	EVT_COMMAND(wxID_ANY, wxEVT_COMMAND_DOWNLOADTHREAD_ERROR, DownloadFrame::OnDownloadStopped)
wxEND_EVENT_TABLE()

DownloadFrame::DownloadFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Quicktech downloader"), wxDefaultPosition, wxSize(500, 100), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
	, panel_(new DownloadPanel(this))
	, installer_(new Installer()) // When should we use installer?
{ }

DownloadFrame::~DownloadFrame()
{ }

void DownloadFrame::Start()
{
	wxURL url(wxT("http://23.253.63.205:8089/quicktech/viewers/QuicktechConnectSetup_x86_1.0.0.1976.msi"));
	downloadThread_ = new DownloadThread(this, url);
	if (downloadThread_->Run() != wxTHREAD_NO_ERROR)
	{
		delete downloadThread_;
		downloadThread_ = NULL;
		wxMessageBox(wxT("Unable to start downloading thread"), wxT("Error"), wxOK);
	}
}

void DownloadFrame::Stop()
{
	//! Todo. Implement functionality to stop downloading.
}

void DownloadFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e))
{
	{
		wxCriticalSectionLocker enter(dtCriticalSection_);
		if (downloadThread_)
		{
			if (downloadThread_->Delete() != wxTHREAD_NO_ERROR)
				wxMessageBox(
				wxT("Can't delete the thread!"), wxT("Frame destruction error"), wxICON_ERROR);
		}
	}

	while (true)
	{
		{
			wxCriticalSectionLocker enter(dtCriticalSection_);
			if (!downloadThread_)
				break;
		}
		wxThread::This()->Sleep(1);
	}

	Destroy();
}

void DownloadFrame::OnDownloadCompleated(wxCommandEvent& WXUNUSED(e))
{
	wxMessageBox(wxT("Download compleated"), wxT("Quicktech downloader"), wxOK);
}

void DownloadFrame::OnDownloadStopped(wxCommandEvent& WXUNUSED(e))
{ }

} // namespace downloader