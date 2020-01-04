#pragma once

#include "FTPList.h"

namespace ftp
{

class FTPListLocal : public FTPList
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	FTPListLocal(wxWindow* parent);
	//! Destructor.
	~FTPListLocal();

	//
	// Public types.
	//
public:
	//! Travers container type.
	typedef wxVector<std::pair<bool, wxString>> TraverseContainer;
	//! Directory traversal type.
	class DirTraverser : public wxDirTraverser
	{
		//
		// Constructor.
		//
	public:
		DirTraverser(TraverseContainer& files)
			: files_(files)
		{ }

		//
		// Public interface.
		//
	public:
		//! This function is called for each file.
		virtual wxDirTraverseResult OnFile(const wxString& filename)
		{
			files_.push_back(std::make_pair(true, filename));
			return wxDIR_CONTINUE;
		}
		//! This function is called for each directory
		virtual wxDirTraverseResult OnDir(const wxString& filename)
		{
			files_.push_back(std::make_pair(false, filename));
			return  wxDIR_IGNORE;
		}
		//! This function is called for each directory which we failed to open for enumerating
		virtual wxDirTraverseResult OnOpenError(const wxString& filename)
		{
			return  wxDIR_IGNORE;
		}

		//
		//! Private data members.
		//
	private:
		//! Result container.
		TraverseContainer& files_;
	};

	//
	// Public interface.
	//
public:
	//! Changes root directory.
	void ChangeRoot(wxString dirname);
	//! Returns selected file.
	wxString GetSelectedFile();
	//! Updates list.
	void UpdateList();

	//
	// Private interface.
	//
private:
	//! The item has been activated.
	void OnActivated(wxListEvent& e);
	//! On item select event handler.
	void OnItemSelect(wxListEvent& e);
	//! Scans directory.
	void ScanPath(const wxString& dirname);
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

};

};