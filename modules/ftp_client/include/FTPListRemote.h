#pragma once

#include "FTPList.h"

namespace ftp
{

//! Forward declaration.
class FTPClient;

class FTPListRemote : public FTPList
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	FTPListRemote(wxWindow* parent);
	//! Destructor.
	~FTPListRemote();

	//
	// Public interface.
	//
public:
	//! Connect to the remote server.
	void Connect(
		const wxString& username,
		const wxString password,
		const wxString& ipAddress,
		const int& port);
	//! Clears list.
	void Clear();
	//! Changes root directory.
	void ChangeRoot(wxString dirname);
	//! Downloads.
	void Download(wxString destination);
	//! Up[loads
	void Upload(wxString source);
	//! Updates list.
	void UpdateList();

	//
	// Public interface.
	//
public:
	//! Scans directory.
	void ScanPath(const wxString& dirname);
	//! The item has been activated.
	void FTPListRemote::OnActivated(wxListEvent& e);
	//! On item select event handler.
	void OnItemSelect(wxListEvent& e);
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! FTP client pointer.
	wxSharedPtr<FTPClient> ftpClient_;
};

};