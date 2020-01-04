#pragma once

namespace downloader
{

//! Forward declaration.
class DownloadPanel;
class DownloadThread;
class Installer;

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

	//! Allow it to access our DownloadThreadPtr.
	friend class DownloadThread;

	//
	// Public types.
	//
public:
	//! DownloadPanel pinter type.
	typedef DownloadPanel* DownloadPanelPtr;
	//! Download thread pointer type.
	typedef DownloadThread* DownloadThreadPtr;
	//! Installer smart pointer type.
	typedef wxSharedPtr<Installer> InstallerPtr;

	//
	// Public interface.
	//
public:
	//! Starts downloading.
	void Start();
	//! Stops downloading.
	void Stop();

	//
	// Private interface.
	//
/*private:*/
	//! On close event handler.
	void OnCloseWindow(wxCloseEvent& WXUNUSED(e));
	//! On download completed handler.
	void OnDownloadCompleated(wxCommandEvent& WXUNUSED(e));
	//! On download stopped handler.
	void OnDownloadStopped(wxCommandEvent& WXUNUSED(e));
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! Panel pointer.
	DownloadPanelPtr panel_;
	// Protects the download thread pointer.
	wxCriticalSection dtCriticalSection_;
	//! Download thread pointer.
	DownloadThreadPtr downloadThread_;
	//! Installer pointer.
	InstallerPtr installer_;
};

} // namespace downloader