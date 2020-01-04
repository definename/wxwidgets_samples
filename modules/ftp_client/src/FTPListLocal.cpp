#include "pch.h"
#include "FTPListLocal.h"

namespace ftp
{

wxBEGIN_EVENT_TABLE(FTPListLocal, wxListCtrl)
	EVT_LIST_ITEM_ACTIVATED(wxID_ANY, FTPListLocal::OnActivated)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, FTPListLocal::OnItemSelect)
wxEND_EVENT_TABLE()

FTPListLocal::FTPListLocal(wxWindow* parent)
	: FTPList(parent)
{ }

FTPListLocal::~FTPListLocal()
{ }

void FTPListLocal::ChangeRoot(wxString dirname)
{
	root_ = wxFileName(dirname).GetPath();
	ScanPath(dirname);
	SetCurrectDir(dirname);
}

void FTPListLocal::OnActivated(wxListEvent& e)
{
	try
	{
		long index = e.GetIndex();
		if (index == 0)
			ChangeRoot(root_);
		else if (!container_[index].isFile_)
			ChangeRoot(container_[index].name_);
		else if (container_[index].isFile_)
		{
			wxFileName file(container_[index].name_);
			wxSharedPtr<wxFileType> ft(wxTheMimeTypesManager->GetFileTypeFromExtension(file.GetExt()));
			if (!ft)
				throw std::runtime_error(
				wxString("Invalid file type pointer").ToUTF8());
			wxString type;
			if (!ft->GetMimeType(&type))
				throw std::runtime_error(
				wxString("Unable to get MIME type specification for this file type").ToUTF8());
			wxString cmd;
			if (!ft->GetOpenCommand(&cmd, wxFileType::MessageParameters(file.GetFullPath(), type)))
				throw std::runtime_error(
				wxString("Do not know how to open this file type").ToUTF8());

			wxExecute(cmd, wxEXEC_ASYNC);
		}
	}
	catch (const std::exception& e)
	{
		wxMessageBox(wxString(e.what()).ToStdWstring(), wxT("Error"), wxICON_ERROR);
	}
}

void FTPListLocal::ScanPath(const wxString& dirname)
{
	TraverseContainer files;
	DirTraverser traverser(files);

	if (!wxDir::Exists(dirname))
		throw std::runtime_error(wxString::Format(wxT("Path %s does not exist"), dirname).ToUTF8());

	wxDir dir(dirname);
	if (!dir.IsOpened())
		throw std::runtime_error(wxString::Format(wxT("Unable to open %s"), dirname).ToUTF8());

	dir.Traverse(traverser, wxEmptyString, wxDIR_FILES | wxDIR_DIRS);

	ReInitialize(container_);

	for (int i = 0; i != files.size(); ++i)
	{
		ListItem item;
		item.isFile_ = files[i].first;
		item.name_ = files[i].second;

		wxFileName file(item.name_);
		if (item.isFile_)
		{
			item.ext_ = file.GetExt();
			item.size_ = wxFileName::GetHumanReadableSize(file.GetSize(), item.name_);
			item.date_ = file.GetModificationTime().Format();
		}
		else
		{
			item.ext_ = wxT("");
			item.size_ = wxT("dir");
			item.date_ = wxT("");
		}

		container_.insert(std::make_pair(i + 1, item));
	}

	SetItemCount(container_.size());
}

void FTPListLocal::OnItemSelect(wxListEvent& e)
{
	long index = e.GetIndex();
	if (index != 0)
		selectedIndex_ = index;
}

wxString FTPListLocal::GetSelectedFile()
{
	auto it = container_.find(selectedIndex_);
	if (it == container_.end())
		throw std::runtime_error("Unable to find item with given index");
	if (!it->second.isFile_)
		throw std::runtime_error("Please select file to transfer");

	return it->second.name_;
}

void FTPListLocal::UpdateList()
{
	ChangeRoot(GetCurrectDir());
}

}