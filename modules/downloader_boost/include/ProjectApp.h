#pragma once

namespace downloader
{

class ProjectApp : public wxApp
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	ProjectApp();
	//! destructor.
	~ProjectApp();

	//
	// Public interface.
	//
public:
	//! Initializes the application.
	virtual bool OnInit(void);
	//! Called after the command line had been successfully parsed.
	virtual bool OnCmdLineParsed(wxCmdLineParser& parser);
	//! Initializes the parser with the command line options for this application
	virtual void OnInitCmdLine(wxCmdLineParser& parser);
	//! Is no tray mode.
	bool IsNoTrayMode() const;
	//! Is silent mode.
	bool IsSilentMode() const;
	//! Is update mode.
	bool IsUpdateMode() const;

	//
	// Public data members.
	//
private:
	//! Silent mode flag.
	bool isSilentMode_;
	//! Update mode flag.
	bool isUpdateMode_;
	//! No tray mode flag.
	bool isNoTrayMode_;
};

static const wxCmdLineEntryDesc cmdLineDesc[] =
{
	{ wxCMD_LINE_SWITCH, "s", "silent", "Provides silent installation.",
	wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
	{ wxCMD_LINE_SWITCH, "u", "update", "Is downloader running in the update mode.",
	wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
	{ wxCMD_LINE_SWITCH, "nt", "notray", "Is downloader running when user is logged off.",
	wxCMD_LINE_VAL_STRING, wxCMD_LINE_PARAM_OPTIONAL },
	{ wxCMD_LINE_NONE }
};

wxDECLARE_APP(ProjectApp);

}; // namespace downloader