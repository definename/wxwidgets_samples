#pragma once

namespace downloader
{

// Declare a new type of event, to be used by our DownloadThread class:
wxDECLARE_EVENT(wxEVT_COMMAND_DOWNLOADTHREAD_COMPLETED, wxCommandEvent);
wxDECLARE_EVENT(wxEVT_COMMAND_DOWNLOADTHREAD_ERROR, wxCommandEvent);

//! Forward declaration.
class DownloadFrame;

class DownloadThread : public wxThread
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	DownloadThread(DownloadFrame* owner, wxURL& url);
	//! Destructor.
	~DownloadThread();

	//
	// Protected interface.
	//
protected:
	//! Entry point of the thread.
	virtual ExitCode Entry();

	//
	// Private interface.
	//
private:
	//! Downloads.
	void Download(wxURL& url, fs::path dest);
	//! Writes all bytes readable from istr to ostr.
	ssize_t DownloadThread::CopyStreamUnbuffered(wxInputStream& istr, wxOutputStream& ostr);
	//! Queue an event for processing on the given object.
	void QueueEvent(wxCommandEvent* e, const wxString& s = wxT(""));

	//
	// Protected data members.
	//
protected:
	//! Owner pointer.
	DownloadFrame* ownerPtr_;
	//! Installer url.
	wxURL url_;
	
};

} // namespace downloader