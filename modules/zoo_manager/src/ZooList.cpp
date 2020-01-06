#include "pch.h"
#include "ZooList.h"

namespace zoo
{

ZooList::ZooList(wxWindow* parent)
	: wxListCtrl(parent, wxID_ANY, wxDefaultPosition, parent->GetSize(), wxLC_REPORT | wxLC_VIRTUAL | wxBORDER_THEME | wxLC_EDIT_LABELS) {

	wxListItem name;
	name.SetId(0);
	name.SetText(wxT("Name"));
	name.SetWidth(100);
	InsertColumn(name.GetId(), name);

	wxListItem gender;
	gender.SetId(1);
	gender.SetText(wxT("Gender"));
	gender.SetWidth(100);
	InsertColumn(gender.GetId(), gender);

	wxListItem age;
	age.SetId(2);
	age.SetText(wxT("Age"));
	age.SetWidth(100);
	InsertColumn(age.GetId(), age);

	wxListItem cell;
	cell.SetId(3);
	cell.SetText(wxT("Cell"));
	cell.SetWidth(100);
	InsertColumn(cell.GetId(), cell);
}

ZooList::~ZooList() {
}

} // namespace zoo
