#include "pch.h"
#include "DownloadFrame.h"
#include "DownloadPanel.h"
#include "DownloadUtils.h"
#include "Downloader.h"
#include "Installer.h"
#include "ProjectApp.h"

namespace downloader
{

wxDEFINE_EVENT(CustomEvent, wxCommandEvent);

wxBEGIN_EVENT_TABLE(DownloadFrame, wxFrame)
	EVT_CLOSE(DownloadFrame::OnCloseWindow)
	EVT_COMMAND(wxID_ANY, CustomEvent, DownloadFrame::CustomEventHandler)
wxEND_EVENT_TABLE()

DownloadFrame::DownloadFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Quicktech downloader"), wxDefaultPosition, wxSize(500, 100), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
	, downloader_(new Downloader())
	, installer_(new Installer())
	, panel_(new DownloadPanel(this))
{
	SetIcon(wxICON(IDI_ICON));

	downloader_->DoOnCompletedSignal(boost::bind(&DownloadFrame::Post, this, DownloadingCompleted, ""));
	downloader_->DoOnErrorSignal(boost::bind(&DownloadFrame::Post, this, DownloadingError, _1));
	downloader_->DoOnStartedSignal(boost::bind(&DownloadFrame::Post, this, DownloadingStarted, ""));

	installer_->DoOnErrorSignal(boost::bind(&DownloadFrame::Post, this, InstallationError, _1));
	installer_->DoOnCompletedSignal(boost::bind(&DownloadFrame::Post, this, InstallationCompleted, ""));

	panel_->DoOnCancelSignal(boost::bind(&DownloadFrame::CancelDownloading, this));
}

DownloadFrame::~DownloadFrame()
{ }

void DownloadFrame::CustomEventHandler(wxCommandEvent& e)
{
	try
	{
		if (e.GetId() == DownloadingCompleted)
		{
			Downloader::DownloadType dType = downloader_->GetType();
			if (dType == Downloader::DownloadFileVersion)
			{
				Downloader::FileBuffer& stream = downloader_->GetBuffer();
				wxURI uri(utils::ParseInstallerLink(stream));

				downloader_->SetType(Downloader::DownloadInstaller);
				downloader_->Start(
					uri.GetServer().ToStdString(),
					uri.GetPort().ToStdString(),
					uri.GetPath().ToStdString());

				panel_->Completed(wxT("Installer file version has been downloaded."));
			}
			else if (dType == Downloader::DownloadInstaller)
			{
				Downloader::FileBuffer& stream = downloader_->GetBuffer();

				boost::filesystem::path msiPath = boost::filesystem::temp_directory_path();
				msiPath /= "quicktech_agent.msi";
				std::ofstream dest(msiPath.c_str(), std::ios::binary);
				if (!dest)
					BOOST_THROW_EXCEPTION(std::runtime_error("Unable to open destination file"));

				dest << stream->rdbuf();
				dest.close();

				panel_->Completed(wxT("Installer image has been downloaded."));
				installer_->Install(msiPath);

				if (IsShown())
					Show(false);
			}
		}
		else if (e.GetId() == DownloadingError)
		{
			panel_->Error();
			const std::string error = e.GetString();

			if (!wxGetApp().IsSilentMode())
				wxMessageBox(error, wxT("Downloading error"), wxICON_ERROR);

			Destroy();
		}
		else if (e.GetId() == DownloadingStarted)
		{
			panel_->Started();
		}
		else if (e.GetId() == InstallationError)
		{
			panel_->Error();
			const std::string error = e.GetString();

			if (!wxGetApp().IsSilentMode())
				wxMessageBox(CU2CW(error.c_str()), wxT("Installation error"), wxICON_ERROR);

			Destroy();
		}
		else if (e.GetId() == InstallationCompleted)
		{
			Destroy();
		}
	}
	catch (const std::exception& e)
	{
		if (!wxGetApp().IsSilentMode())
			wxMessageBox(CU2CW(e.what()), wxT("Downloader error"), wxICON_ERROR);

		Destroy();
	}
}

void DownloadFrame::StartDownloading()
{
	wxArchitecture arch = wxPlatformInfo().GetArchitecture();
	wxString path("/quicktech/agents/");
	path.append((arch == wxARCH_64) ? "x64" : "x86");
	path.append("/version.cfg");
	downloader_->SetType(Downloader::DownloadFileVersion);
	downloader_->Start(
		"23.253.63.205",
		"8089",
		path.ToStdString());
}

void DownloadFrame::Post(const EventType& type, const std::string& msg /* = "" */)
{
	wxCommandEvent e(CustomEvent, type);
	e.SetString(msg.c_str());
	wxPostEvent(this, e);
}

void DownloadFrame::CancelDownloading()
{
	if (downloader_)
		downloader_->Stop();
}

void DownloadFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e))
{
	if (downloader_)
		downloader_->Stop();
	if (installer_)
		installer_->Stop();

	Destroy();
}

} // namespace downloader