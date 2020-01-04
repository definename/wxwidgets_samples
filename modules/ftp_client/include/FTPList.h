#pragma once

namespace ftp
{

class FTPList : public wxListCtrl
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	FTPList(wxWindow* parent);
	//! Destructor.
	~FTPList();

	//
	// Public types.
	//
public:
	//! List file type.
	struct ListItem
	{
		//! Is file.
		bool isFile_;
		//! File/Dir name.
		wxString name_;
		//! File extension.
		wxString ext_;
		//! File size.
		wxString size_;
		//! File/Dir date.
		wxString date_;
	};
	//! Column type.
	//typedef std::vector<wxString> Columns;
	//! Item type.
	typedef long Index;
	//! List type.
	typedef std::map<Index, ListItem> Container;

	//
	// Public interface.
	//
public:
	//! Initializes list.
	void Initialize(Container& container);
	//! Re initializes list.
	void ReInitialize(Container& container);
	//! Returns current directory.
	wxString GetCurrectDir() const;
	//! Sets current directory.
	void SetCurrectDir(const wxString& dir);

	//
	// Private interface.
	//
private:
	//! Returns the index of the items image in the controls image list or -1 for no image.
	virtual int OnGetItemImage(long item) const;
	//! It returns the string containing the text of the given column for the specified item.
	virtual wxString OnGetItemText(long item, long column) const;
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
protected:
	//! Container.
	Container container_;
	//! Root directory.
	wxString root_;
	//! Selected index.
	int selectedIndex_;
	//! Current directory.
	wxString currentDir_;
};

}; // namespace null_app