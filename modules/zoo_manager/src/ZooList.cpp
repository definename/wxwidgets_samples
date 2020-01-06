#include "pch.h"
#include "ZooList.h"

namespace zoo
{

wxBEGIN_EVENT_TABLE(ZooList, wxListCtrl)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, ZooList::OnItemSelect)
wxEND_EVENT_TABLE()

const static long listFlags = wxLC_REPORT | wxLC_VIRTUAL | wxBORDER_THEME | wxLC_EDIT_LABELS | wxLC_SINGLE_SEL;

ZooList::ZooList(wxWindow* parent)
	: wxListCtrl(parent, wxID_ANY, wxDefaultPosition, parent->GetSize(), listFlags)
	, selectIndex_(-1) {

	wxListItem name;
	name.SetId(ZooDataId::ID_NAME);
	name.SetText(wxT("Name"));
	name.SetWidth(100);
	InsertColumn(name.GetId(), name);

	wxListItem gender;
	gender.SetId(ZooDataId::ID_GENDER);
	gender.SetText(wxT("Gender"));
	gender.SetWidth(100);
	InsertColumn(gender.GetId(), gender);

	wxListItem age;
	age.SetId(ZooDataId::ID_AGE);
	age.SetText(wxT("Age"));
	age.SetWidth(100);
	InsertColumn(age.GetId(), age);

	wxListItem cell;
	cell.SetId(ZooDataId::ID_CELL);
	cell.SetText(wxT("Cell"));
	cell.SetWidth(100);
	InsertColumn(cell.GetId(), cell);

	for (int i = 0; i != 5; ++i) {
		wxString str;
		str.Printf("Elephant%d", i);
		ZooDataPtr zooData = ZooDataPtr(new ZooData(str.ToStdWstring(), wxT("Vasya"), wxT("male"), wxT("12")));
		zooHash_.insert(ZooHash::value_type(i, zooData));
	}
}

ZooList::~ZooList() {
	zooHash_.clear();
}

bool ZooList::AddItem(ZooDataPtr zooData) {
	ZooHash::Insert_Result res = zooHash_.insert(ZooHash::value_type(zooHash_.size(), zooData));
	Update();
	return res.second;
}

bool ZooList::UpdateItem(const long& index, ZooDataPtr zooDataNew) {
	bool ret = false;
	ZooDataPtr zooDataOld;
	if (GetItem(index, zooDataOld)) {
		zooDataOld->name_ = zooDataNew->name_;
		zooDataOld->gender_ = zooDataNew->gender_;
		zooDataOld->age_ = zooDataNew->age_;
		zooDataOld->cell_ = zooDataNew->cell_;
		RefreshItem(index);
		ret = true;
	}
	return ret;
}

bool ZooList::RemoveItem(const long& index) {
	bool ret = false;
	ZooHash::iterator it = zooHash_.find(index);
	if (it != zooHash_.end()) {
		long lastIndex = zooHash_.size() - 1;
		it->second = zooHash_[lastIndex];
		zooHash_.erase(lastIndex);
		ret = true;
		RefreshItem(index);
		Update();
	}
	return ret;
}

bool ZooList::GetItem(const int index, ZooDataPtr& zooData) {
	bool ret = false;
	ZooHash::iterator it = zooHash_.find(index);
	if (it != zooHash_.end()) {
		zooData = it->second;
		ret = true;
	}
	return ret;
}

void ZooList::Update() {
	SetItemCount(zooHash_.size());
}

wxString ZooList::OnGetItemText(long item, long column) const {
	ZooHash::const_iterator it = zooHash_.find(item);
	if (it != zooHash_.end()) {
		if (column == ZooDataId::ID_NAME) {
			return it->second->name_;
		}
		else if (column == ZooDataId::ID_GENDER) {
			return it->second->gender_;
		}
		else if (column == ZooDataId::ID_AGE) {
			return it->second->age_;
		}
		else if (column == ZooDataId::ID_CELL) {
			return it->second->cell_;
		}
	}
	return wxT("Unknown");
}

void ZooList::OnItemSelect(wxListEvent& e)
{
	selectIndex_ = e.GetIndex();
}

bool ZooList::GetSelectedIndex(long& index) {
	bool ret = true;
	const int count = GetSelectedItemCount();
	if (count == 0) {
		selectIndex_ = -1;
		ret = false;
	}
	index = selectIndex_;
	return ret;
}


} // namespace zoo
