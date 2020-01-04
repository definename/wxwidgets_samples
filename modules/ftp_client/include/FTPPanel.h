#pragma once

namespace ftp
{

//! Forward declaration.
class FTPListLocal;
class FTPListRemote;
class TextControl;
class SplitterWindow;
class VolumeController;

class FTPPanel : public wxPanel
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	FTPPanel(wxWindow* parent);
	//! Destructor.
	~FTPPanel();

	//
	// Public types.
	//
public:
	//!  Identifier type
	enum IDs
	{
		ID_CONNECT = 0
	};
	//! Bitmap button pointer type.
	typedef wxBitmapButton* BitmapButtonPtr;
	//! Local FTP list pointer type.
	typedef FTPListLocal* FTPListLocalPtr;
	//! Remote FTP list pointer type.
	typedef FTPListRemote* FTPListRemotePtr;
	//! Splitter window pointer type.
	typedef SplitterWindow* SplitterWindowPtr;
	//! Text control pointer type.
	typedef TextControl* TextControlPtr;
	//! Volume controller.
	typedef VolumeController* VolumeControllerPtr;

	//
	// Public interface.
	//
public:
	//! Downloads.
	void Download();
	//! Uploads.
	void Upload();

	//
	// Private interface.
	//
private:
	//! On button event handler.
	void OnLogin(wxCommandEvent& event);
	//! Initializes buttons.
	void InitializePanel(wxBoxSizer* sizer);
	//! Initializes ftp lists.
	void InitializeSplitter(wxBoxSizer* sizer);
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! Login button.
	BitmapButtonPtr btnLogin_;
	//! host pointer.
	TextControlPtr ip_;
	//! Local list pointer.
	FTPListLocalPtr listLocal_;
	//! Remote list pointer.
	FTPListRemotePtr listRemote_;
	//! Password text pointer.
	TextControlPtr password_;
	//! Port text pointer.
	TextControlPtr port_;
	//! Username text pointer.
	TextControlPtr username_;
	//! Volume Controller.
	VolumeControllerPtr volumeController_;
};

}; // namespace null_app