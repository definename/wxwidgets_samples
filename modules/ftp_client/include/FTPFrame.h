#pragma once

namespace ftp
{

//! Forward declaration
class FTPPanel;

class FTPFrame : public wxFrame
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	FTPFrame();
	//! destructor.
	~FTPFrame();

	//
	// Public types.
	//
public:
	enum IDs
	{
		ID_MENU_EXIT = 0,
		ID_MENU_ABOUT,
		ID_DOWNLOAD,
		ID_UPLOAD
	};
	//! FTP panel pointer type.
	typedef FTPPanel* FTPPanelPtr;

	//
	// Private interface.
	//
private:
	//! On about event handler.
	void OnAbout(wxCommandEvent& WXUNUSED(e));
	//! On download event handler.
	void OnDownlaod(wxCommandEvent& WXUNUSED(e));
	//! On upload event handler.
	void OnUpload(wxCommandEvent& WXUNUSED(e));
	//! On exit menu handler.
	void FTPFrame::OnExit(wxCommandEvent& WXUNUSED(e));
	//! On close event handler.
	void FTPFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e));
	//! Initializes menu.
	void InitializeMenu();
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! FTP panel pointer.
	FTPPanelPtr ftpPanel_;
};

}; // namespace null_app