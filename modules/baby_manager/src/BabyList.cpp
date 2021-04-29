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

	Bind(wxEVT_DESTROY, &BabyList::OnDestroy, this);
	Bind(wxEVT_THREAD, &BabyList::OnThreadEvent, this);

	// Launch thread
	if (CreateThread(wxTHREAD_JOINABLE) == wxTHREAD_NO_ERROR) {
		if (GetThread()->Run() != wxTHREAD_NO_ERROR) {
			wxMessageBox(wxT("Failed to run list thread, sorting stuff won't work"));
		}
	}

	wxListItem item;
	item.SetWidth(100);
	item.SetImage(-1);

	item.SetId(BabyDataId::ID_NAME);
	item.SetText(BABY_NAME);
	InsertColumn(item.GetId(), item);

	item.SetId(BabyDataId::ID_GENDER);
	item.SetText(BABY_GENDER);
	InsertColumn(item.GetId(), item);

	item.SetId(BabyDataId::ID_BLOOD_TYPE);
	item.SetText(BABY_BLOOD);
	InsertColumn(item.GetId(), item);

	item.SetId(BabyDataId::ID_APGAR_SCORE);
	item.SetText(BABY_APGAR);
	InsertColumn(item.GetId(), item);

	// De-serialize container.
	if (db_path.FileExists()) {
		std::ifstream ifile(db_path.GetFullPath().ToStdWstring(), std::ios::in | std::ios::binary);
		DeserializeFrom<boost::archive::binary_iarchive>(ifile, hash_);
	}
}

BabyList::~BabyList() {
	try {
		// Serialize container.
		std::ofstream ofile(db_path.GetFullPath().ToStdWstring(), std::ios::out | std::ios::binary);
		SerializeTo<boost::archive::binary_oarchive>(hash_, ofile);
	} catch (std::exception&) {
		wxMessageBox(wxT("Failed to serialize zoo data"), wxT("Serialize zoo data"), wxICON_WARNING, this);
	}
	hash_.swap(BabyHash());
}

void BabyList::AddItem(BabyDataPtr data) {
	if (data) {
		hash_.push_back(data);
		Update();
	}
}

void BabyList::UpdateItem(const long& index, BabyDataPtr dataNew) {
	BabyDataPtr dataOld;
	if (dataNew && GetItem(index, dataOld)) {
		dataOld->name_ = dataNew->name_;
		dataOld->gender_ = dataNew->gender_;
		dataOld->blood_ = dataNew->blood_;
		dataOld->apgar_ = dataNew->apgar_;
		RefreshItem(index);
	}
}

void BabyList::RemoveItem(const long& index) {
	if (index < hash_.size()) {
		BabyHash::value_type last = hash_[hash_.size() - 1];
		hash_[index] = last;
		hash_.pop_back();
		RefreshItem(index);
		Update();
	}
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
		} else if (column == BabyDataId::ID_GENDER) {
			return data->gender_;
		} else if (column == BabyDataId::ID_BLOOD_TYPE) {
			return data->blood_;
		} else if (column == BabyDataId::ID_APGAR_SCORE) {
			return data->apgar_;
		}
	}
	return wxT("Unknown");
}

int BabyList::OnGetItemColumnImage(long WXUNUSED(item), long WXUNUSED(column)) const {
	// This handler was defined to make compiler happy
	return -1;
}

void BabyList::OnItemSelect(wxListEvent& e) {
	selectIndex_ = e.GetIndex();
}

void BabyList::OnColClick(wxListEvent& e) {
	ThreadQueue::Message m = static_cast<BabyDataId>(e.GetColumn());
	threadQueue_.Post(m);
}

void BabyList::OnThreadEvent(wxThreadEvent& e) {
	// Update column icon
	int column = e.GetInt();
	wxListItem item;
	item.SetMask(wxLIST_MASK_IMAGE);
	for (int i = 0; i < GetColumnCount(); ++i) {
		item.SetImage(i == column ? 0 : -1);
		SetColumn(i, item);
	}
	// Update list control
	long top_visible = GetTopItem();
	long visible_count = GetCountPerPage();
	RefreshItems(top_visible, top_visible + visible_count);
}

void BabyList::OnDestroy(wxWindowDestroyEvent& WXUNUSED(e)) {
	if (GetThread() && GetThread()->IsRunning()) {
		threadQueue_.Clear();
		threadQueue_.Post(BabyDataId::ID_UNKNOWN);
		GetThread()->Wait();
	}
}

wxThread::ExitCode BabyList::Entry() {
	while (!GetThread()->TestDestroy()) {
		ThreadQueue::Message m = BabyDataId::ID_UNKNOWN;
		if (threadQueue_.ReceiveTimeout(0.5, m) == wxMSGQUEUE_TIMEOUT) {
			continue;
		}

		if (m == BabyDataId::ID_APGAR_SCORE) {
			static bool apgar_ascending = true;
			apgar_ascending = !apgar_ascending;
			std::sort(hash_.begin(), hash_.end(), [](const BabyHash::value_type & l, const BabyHash::value_type & r) {
				int lapgar = std::stoi(l->apgar_);
				int rapgar = std::stoi(r->apgar_);
				if (apgar_ascending) {
					return lapgar < rapgar;
				}
				else {
					return lapgar > rapgar;
				}
				});
		} else if (m == BabyDataId::ID_BLOOD_TYPE) {
			static bool blood_ascending = true;
			blood_ascending = !blood_ascending;
			std::sort(hash_.begin(), hash_.end(), [](const BabyHash::value_type & l, const BabyHash::value_type & r) {
				return std::lexicographical_compare(
					l->blood_.begin(), l->blood_.end(),
					r->blood_.begin(), r->blood_.end(),
					[](const string_type::value_type & c1, const string_type::value_type & c2) {
						if (blood_ascending) {
							return std::toupper(c1) < std::toupper(c2);
						}
						else {
							return std::toupper(c1) > std::toupper(c2);
						}
					});
				});
		} else if (m == BabyDataId::ID_GENDER) {
			static bool gender_ascending = true;
			gender_ascending = !gender_ascending;
			std::sort(hash_.begin(), hash_.end(), [](const BabyHash::value_type & l, const BabyHash::value_type & r) {
				return std::lexicographical_compare(
					l->gender_.begin(), l->gender_.end(),
					r->gender_.begin(), r->gender_.end(),
					[](const string_type::value_type & c1, const string_type::value_type & c2) {
						if (gender_ascending) {
							return std::toupper(c1) < std::toupper(c2);
						}
						else {
							return std::toupper(c1) > std::toupper(c2);
						}
					});
				});
		} else if (m == BabyDataId::ID_NAME) {
			static bool name_ascending = true;
			name_ascending = !name_ascending;
			std::sort(hash_.begin(), hash_.end(), [](const BabyHash::value_type & l, const BabyHash::value_type & r) {
				return std::lexicographical_compare(
					l->name_.begin(), l->name_.end(),
					r->name_.begin(), r->name_.end(),
					[](const string_type::value_type & c1, const string_type::value_type & c2) {
						if (name_ascending) {
							return std::toupper(c1) < std::toupper(c2);
						}
						else {
							return std::toupper(c1) > std::toupper(c2);
						}
					});
				});
		} else if (m == BabyDataId::ID_UNKNOWN) {
			break;
		} else {
			continue;
		}

		// Update list control
		wxThreadEvent* e = new wxThreadEvent();
		e->SetInt(m);
		wxQueueEvent(GetEventHandler(), e);
	}
	return (wxThread::ExitCode)0;
}

}
