#pragma once

namespace downloader
{

class DownloadPanel : public wxPanel
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	DownloadPanel(wxWindow* parent);
	//! Destructor.
	~DownloadPanel();

	//
	// Public types.
	//
public:
	//! Button pointer type.
	typedef wxButton* ButtonPtr;
	//! Box sizer pointer type.
	typedef wxBoxSizer* BoxSizerPtr;
	//! Activity indicator pointer type.
	typedef wxActivityIndicator* ActivityIndicatorPtr;
	//! Static text pointer type.
	typedef wxStaticText* StaticTextPtr;


	//
	// Private interface.
	//
private:
	//! On cancel event handler.
	void OnCancel(wxCommandEvent& WXUNUSED(e));
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! Activity indicator.
	ActivityIndicatorPtr activityInd_;
	//! Download button.
	ButtonPtr downloadBtn_;
	//! Static text.
	StaticTextPtr text_;
	//! Top sizer.
	BoxSizerPtr topSizer_;
	//! Activity sizer.
	BoxSizerPtr activitySizer_;
	//! Text sizer.
	BoxSizerPtr textSizer_;
	//! Button sizer.
	BoxSizerPtr btnSizer_;
};

} // namespace downloader