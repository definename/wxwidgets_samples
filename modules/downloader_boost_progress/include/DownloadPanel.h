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
	//! Gauge range type.
	enum Range
	{
		MAXRANGE = 100
	};
	//! Box sizer pointer type.
	typedef wxBoxSizer* BoxSizerPtr;
	//! Activity indicator pointer type.
	typedef wxActivityIndicator* ActivityIndicatorPtr;
	//! Static text pointer type.
	typedef wxStaticText* StaticTextPtr;
	//! Gauge pointer type.
	typedef wxGauge* GaugePtr;

	//
	// Public interface.
	//
public:
	//! Handles file version complete event.
	void DownloadedFileVersion(const wxString& lable);
	//! Handles installer complete event.
	void DownloadedInstaller(const wxString& lable);
	//! Handles error.
	void Error();
	//! Handles gauge progress.
	void Progress();
	//! Handles start.
	void Started();

	//
	// Private interface.
	//
private:
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	//! Activity indicator.
	ActivityIndicatorPtr activityInd_;
	//! Activity sizer.
	BoxSizerPtr activitySizer_;
	//! Gauge.
	GaugePtr gauge_;
	//! Gauge sizer.
	BoxSizerPtr gaugeSizer_;
	//! Gauge text.
	StaticTextPtr textGauge_;
	//! Top sizer.
	BoxSizerPtr topSizer_;
	//! Version text.
	StaticTextPtr textVersion_;
};

} // namespace downloader