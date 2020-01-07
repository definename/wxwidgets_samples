#pragma once

#include "ZooTypes.h"

namespace zoo
{

class ZooList: public wxListCtrl
{
	// Construction and destruction.
public:
	// Constructor.
	ZooList(wxWindow* parent);
	// Destructor.
	~ZooList();

	// Public types.
public:
	// Zoo data id.
	enum ZooDataId {
		ID_NAME = 0,
		ID_GENDER,
		ID_AGE,
		ID_CELL
	};
	// Public interface.
public:
	// Add.
	bool AddItem(ZooDataPtr zooData);
	// Update item by index.
	bool ZooList::UpdateItem(const long& index, ZooDataPtr zooDataNew);
	// Remove item by index.
	bool ZooList::RemoveItem(const long& index);
	// Get item by index.
	bool ZooList::GetItem(const int index, ZooDataPtr& zooData);

	// Update view.
	void Update();
	// Get index of selected item.
	bool ZooList::GetSelectedIndex(long& index);

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
	ZooHash zooHash_;
	// Selected index.
	long selectIndex_;
};

}; // namespace zoo