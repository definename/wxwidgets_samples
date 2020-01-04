#pragma once

namespace downloader
{

//! Forward declaration.
class DownloadPanel;
class Installer;
class Downloader;

class DownloadFrame : public wxFrame
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	DownloadFrame();
	//! Destructor.
	~DownloadFrame();

	//
	// Public types.
	//
public:
	//! Event types.
	enum EventType
	{
		DownloadingCompleted,
		DownloadingError,
		DownloadingProgress,
		DownloadingStarted,
		InstallationError,
		InstallationCompleted
	};
	//! Downloader smart pointer type.
	typedef wxSharedPtr<Downloader> DownloaderPtr;
	//! DownloadPanel pinter type.
	typedef DownloadPanel* DownloadPanelPtr;
	//! Installer smart pointer type.
	typedef wxSharedPtr<Installer> InstallerPtr;

	//
	// Public interface.
	//
public:
	//! On show event handler.
	void StartDownloading();

	//
	// Private interface.
	//
private:
	//! Handles custom events.
	void CustomEventHandler(wxCommandEvent& e);
	//! On close event handler.
	void OnCloseWindow(wxCloseEvent& WXUNUSED(e));
	//! Posts custom events.
	void Post(const EventType& type, const std::string& msg = "");
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! Downloader pointer.
	DownloaderPtr downloader_;
	//! Installer pointer.
	InstallerPtr installer_;
	//! Panel pointer.
	DownloadPanelPtr panel_;
};

} // namespace downloader