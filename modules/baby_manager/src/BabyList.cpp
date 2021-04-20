#include "pch.h"
#include "BabyList.h"
#include "BabyUtil.h"

namespace baby
{

wxBEGIN_EVENT_TABLE(BabyList, wxListCtrl)
	EVT_LIST_ITEM_SELECTED(BabyControlId::ID_LIST_CTRL, BabyList::OnItemSelect)
	EVT_LIST_COL_CLICK(BabyControlId::ID_LIST_CTRL, BabyList::OnColClick)
wxEND_EVENT_TABLE()

const static long listFlags = wxLC_REPORT | wxLC_VIRTUAL | wxBORDER_THEME | wxLC_EDIT_LABELS | wxLC_SINGLE_SEL | wxLC_HRULES;

BabyList::BabyList(wxWindow* parent)
	: wxListCtrl(parent, BabyControlId::ID_LIST_CTRL, wxDefaultPosition, parent->GetSize(), listFlags)
	, selectIndex_(-1) {

	wxListItem name;
	name.SetId(BabyDataId::ID_NAME);
	name.SetText(BABY_NAME);
	name.SetWidth(100);
	InsertColumn(name.GetId(), name);

	wxListItem gender;
	gender.SetId(BabyDataId::ID_GENDER);
	gender.SetText(BABY_GENDER);
	gender.SetWidth(100);
	InsertColumn(gender.GetId(), gender);

	wxListItem blood;
	blood.SetId(BabyDataId::ID_BLOOD_TYPE);
	blood.SetText(BABY_BLOOD);
	blood.SetWidth(100);
	InsertColumn(blood.GetId(), blood);

	wxListItem apgar;
	apgar.SetId(BabyDataId::ID_APGAR_SCORE);
	apgar.SetText(BABY_APGAR);
	apgar.SetWidth(100);
	InsertColumn(apgar.GetId(), apgar);

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
	hash_.swap(BabyHash());
}

void BabyList::AddItem(BabyDataPtr zooData) {
	hash_.push_back(zooData);
	Update();
}

bool BabyList::UpdateItem(const long& index, BabyDataPtr dataNew) {
	bool ret = false;
	BabyDataPtr dataOld;
	if (GetItem(index, dataOld)) {
		dataOld->name_ = dataNew->name_;
		dataOld->gender_ = dataNew->gender_;
		dataOld->blood_ = dataNew->blood_;
		dataOld->apgar_ = dataNew->apgar_;
		RefreshItem(index);
		ret = true;
	}
	return ret;
}

bool BabyList::RemoveItem(const long& index) {
	bool ret = false;
	if (index < hash_.size()) {
		BabyHash::value_type last = hash_[hash_.size() - 1];
		hash_[index] = last;
		hash_.pop_back();
		ret = true;
		RefreshItem(index);
		Update();
	}
	return ret;
}

bool BabyList::GetItem(const int index, BabyDataPtr& data) {
	bool ret = false;
	if (index < hash_.size()) {
		data = hash_[index];
		ret = true;
	}
	return ret;
}

void BabyList::Update() {
	SetItemCount(hash_.size());
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

wxString BabyList::OnGetItemText(long index, long column) const {
	if (index < hash_.size()) {
		const BabyHash::value_type& data = hash_[index];
		if (column == BabyDataId::ID_NAME) {
			return data->name_;
		}
		else if (column == BabyDataId::ID_GENDER) {
			return data->gender_;
		}
		else if (column == BabyDataId::ID_BLOOD_TYPE) {
			return data->blood_;
		}
		else if (column == BabyDataId::ID_APGAR_SCORE) {
			return data->apgar_;
		}
	}
	return wxT("Unknown");
}

void BabyList::OnItemSelect(wxListEvent& e)
{
	selectIndex_ = e.GetIndex();
}

void BabyList::OnColClick(wxListEvent& e) {
	wxString msg;
	msg.Printf(wxT("col:%d"), e.GetColumn());
	wxMessageBox(msg);
}

}
