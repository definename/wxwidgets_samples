#include "pch.h"
#include "FTPList.h"

namespace ftp
{

wxBEGIN_EVENT_TABLE(FTPList, wxListCtrl)
wxEND_EVENT_TABLE()

FTPList::FTPList(wxWindow* parent)
	: wxListCtrl(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT | wxLC_VIRTUAL | wxBORDER_THEME | wxLC_EDIT_LABELS)
	, selectedIndex_(1)
{
	wxImageList* imageList = new wxImageList(16, 16);
	imageList->Add(wxArtProvider::GetIcon(wxART_GO_TO_PARENT));
	imageList->Add(wxArtProvider::GetIcon(wxART_EXECUTABLE_FILE));
	imageList->Add(wxArtProvider::GetIcon(wxART_FOLDER));
	SetImageList(imageList, wxIMAGE_LIST_SMALL);

	wxListItem col0;
	col0.SetId(0);
	col0.SetText(wxT("Name"));
	col0.SetWidth(100);
	InsertColumn(0, col0);

	wxListItem col1;
	col1.SetId(1);
	col1.SetText(wxT("Ext"));
	col1.SetWidth(100);
	InsertColumn(1, col1);

	wxListItem col2;
	col2.SetId(2);
	col2.SetText(wxT("Size"));
	col2.SetWidth(100);
	InsertColumn(2, col2);

	wxListItem col3;
	col3.SetId(3);
	col3.SetText(wxT("Date"));
	col3.SetWidth(100);
	InsertColumn(3, col3);

	Initialize(container_);
}

FTPList::~FTPList()
{ }

int FTPList::OnGetItemImage(long item) const
{
	if (item == 0)
		return 0;
	else if (container_.at(item).isFile_)
		return 1;

	return 2;
}

wxString FTPList::GetCurrectDir() const
{
	return currentDir_;
}

void FTPList::SetCurrectDir(const wxString& dir)
{
	currentDir_ = dir;
}

void FTPList::Initialize(Container& container)
{
	ListItem item;
	item.name_ = wxT("[..]");
	item.ext_ = wxT("");
	item.size_ = wxT("");
	item.date_ = wxT("");
	item.isFile_ = false;
	container_.insert(std::make_pair(0, item));
}

wxString FTPList::OnGetItemText(long item, long column) const
{
	Container::const_iterator it = container_.find(item);
	if (it == container_.end())
		return wxT("Unknown");

	if (column == 0)
		return wxFileName(it->second.name_).GetFullName();
	else if (column == 1)
		return it->second.ext_;
	else if (column == 2)
		return it->second.size_;
	else if (column == 3)
		return it->second.date_;

	return wxT("Unknown");
}

void FTPList::ReInitialize(Container& container)
{
	DeleteAllItems();
	container_.clear();

	Initialize(container);
}

} // namespace null_app
