#pragma once

#include "BabyTypes.h"

namespace baby
{

class BabyList: public wxListCtrl, public wxThreadHelper
{
	// Construction and destruction.
public:
	// Constructor.
	BabyList(wxWindow* parent);
	// Destructor.
	~BabyList();

	// Public interface.
public:
	// Add.
	void AddItem(BabyDataPtr zooData);
	// Update item by index.
	void BabyList::UpdateItem(const long& index, BabyDataPtr zooDataNew);
	// Remove item by index.
	void BabyList::RemoveItem(const long& index);
	// Get item by index.
	bool BabyList::GetItem(const int index, BabyDataPtr& zooData);

	// Update view.
	void Update();
	// Get index of selected item.
	bool GetSelectedIndex(long& index);

	// Private interface.
private:
	// It returns the string containing the text of the given column for the specified item.
	virtual wxString OnGetItemText(long item, long column) const wxOVERRIDE;
	// Specify the image index for the given line and column
	virtual int OnGetItemColumnImage(long item, long column) const wxOVERRIDE;
	// Entry point of the thread
	virtual wxThread::ExitCode Entry() wxOVERRIDE;
	// Item select handler.
	void OnItemSelect(wxListEvent& e);
	// Column has been left clicked
	void OnColClick(wxListEvent& e);
	// Thread event handler
	void OnThreadEvent(wxThreadEvent& e);
	// Window destroy event handler
	void OnDestroy(wxWindowDestroyEvent& e);

	// Use this macro inside a class declaration to declare a static event table for that class.
	wxDECLARE_EVENT_TABLE();

	// Private types
private:
	// Thread queue type
	using ThreadQueue = wxMessageQueue<BabyDataId>;

	// Private members.
private:
	// Hash map.
	BabyHash hash_;
	// Selected index.
	long selectIndex_;
	// Thread queue
	ThreadQueue threadQueue_;
};

};