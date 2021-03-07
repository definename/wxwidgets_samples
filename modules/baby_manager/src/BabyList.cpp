#include "pch.h"
#include "BabyList.h"
#include "BabyUtil.h"

namespace baby
{

wxBEGIN_EVENT_TABLE(BabyList, wxListCtrl)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, BabyList::OnItemSelect)
wxEND_EVENT_TABLE()

const static long listFlags = wxLC_REPORT | wxLC_VIRTUAL | wxBORDER_THEME | wxLC_EDIT_LABELS | wxLC_SINGLE_SEL;

BabyList::BabyList(wxWindow* parent)
	: wxListCtrl(parent, wxID_ANY, wxDefaultPosition, parent->GetSize(), listFlags)
	, selectIndex_(-1) {

	wxListItem name;
	name.SetId(BabyDataId::ID_NAME);
	name.SetText(wxT("Name"));
	name.SetWidth(100);
	InsertColumn(name.GetId(), name);

	wxListItem gender;
	gender.SetId(BabyDataId::ID_GENDER);
	gender.SetText(wxT("Gender"));
	gender.SetWidth(100);
	InsertColumn(gender.GetId(), gender);

	wxListItem age;
	age.SetId(BabyDataId::ID_AGE);
	age.SetText(wxT("Age"));
	age.SetWidth(100);
	InsertColumn(age.GetId(), age);

	wxListItem cell;
	cell.SetId(BabyDataId::ID_CELL);
	cell.SetText(wxT("Cell"));
	cell.SetWidth(100);
	InsertColumn(cell.GetId(), cell);

	// De-serialize zoo data container.
	if (db_path.FileExists()) {
		std::ifstream ifile(db_path.GetFullPath().ToStdWstring(), std::ios::in | std::ios::binary);
		DeserializeFrom<boost::archive::binary_iarchive>(ifile, hash_);
	}
}

BabyList::~BabyList() {
	try {
		// Serialize zoo data container.
		std::ofstream ofile(db_path.GetFullPath().ToStdWstring(), std::ios::out | std::ios::binary);
		SerializeTo<boost::archive::binary_oarchive>(hash_, ofile);
	}
	catch (std::exception&) {
		wxMessageBox(wxT("Failed to serialize zoo data"), wxT("Serialize zoo data"), wxICON_WARNING, this);
	}
	hash_.clear();
}

bool BabyList::AddItem(BabyDataPtr zooData) {
	auto ret = hash_.insert(BabyHash::value_type(hash_.size(), zooData));
	Update();
	return ret.second;
}

bool BabyList::UpdateItem(const long& index, BabyDataPtr zooDataNew) {
	bool ret = false;
	BabyDataPtr zooDataOld;
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

bool BabyList::RemoveItem(const long& index) {
	bool ret = false;
	BabyHash::iterator it = hash_.find(index);
	if (it != hash_.end()) {
		long lastIndex = hash_.size() - 1;
		it->second = hash_[lastIndex];
		hash_.erase(lastIndex);
		ret = true;
		RefreshItem(index);
		Update();
	}
	return ret;
}

bool BabyList::GetItem(const int index, BabyDataPtr& zooData) {
	bool ret = false;
	BabyHash::iterator it = hash_.find(index);
	if (it != hash_.end()) {
		zooData = it->second;
		ret = true;
	}
	return ret;
}

void BabyList::Update() {
	SetItemCount(hash_.size());
}

wxString BabyList::OnGetItemText(long item, long column) const {
	BabyHash::const_iterator it = hash_.find(item);
	if (it != hash_.end()) {
		if (column == BabyDataId::ID_NAME) {
			return it->second->name_;
		}
		else if (column == BabyDataId::ID_GENDER) {
			return it->second->gender_;
		}
		else if (column == BabyDataId::ID_AGE) {
			return it->second->age_;
		}
		else if (column == BabyDataId::ID_CELL) {
			return it->second->cell_;
		}
	}
	return wxT("Unknown");
}

void BabyList::OnItemSelect(wxListEvent& e)
{
	selectIndex_ = e.GetIndex();
}

bool BabyList::GetSelectedIndex(long& index) {
	bool ret = true;
	const int count = GetSelectedItemCount();
	if (count == 0) {
		selectIndex_ = -1;
		ret = false;
	}
	index = selectIndex_;
	return ret;
}

}
