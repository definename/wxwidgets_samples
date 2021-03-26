#pragma once

#include "BabyTypes.h"

namespace baby
{

class BabyList: public wxListCtrl
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
	bool AddItem(BabyDataPtr zooData);
	// Update item by index.
	bool BabyList::UpdateItem(const long& index, BabyDataPtr zooDataNew);
	// Remove item by index.
	bool BabyList::RemoveItem(const long& index);
	// Get item by index.
	bool BabyList::GetItem(const int index, BabyDataPtr& zooData);

	// Update view.
	void Update();
	// Get index of selected item.
	bool BabyList::GetSelectedIndex(long& index);

	// Private interface.
private:
	// It returns the string containing the text of the given column for the specified item.
	virtual wxString OnGetItemText(long item, long column) const wxOVERRIDE;
	// Item select handler.
	void OnItemSelect(wxListEvent& e);
	// Use this macro inside a class declaration to declare a static event table for that class.
	wxDECLARE_EVENT_TABLE();

	// Private members.
private:
	// Hash map.
	BabyHash hash_;
	// Selected index.
	long selectIndex_;
};

};