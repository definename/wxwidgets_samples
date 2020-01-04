#include "pch.h"
#include "FTPListRemote.h"
#include "FTPClient.h"

namespace ftp
{

wxBEGIN_EVENT_TABLE(FTPListRemote, wxListCtrl)
	EVT_LIST_ITEM_ACTIVATED(wxID_ANY, FTPListRemote::OnActivated)
	EVT_LIST_ITEM_SELECTED(wxID_ANY, FTPListRemote::OnItemSelect)
wxEND_EVENT_TABLE()

FTPListRemote::FTPListRemote(wxWindow* parent)
	: FTPList(parent)
	, ftpClient_(new FTPClient())
{
	SetItemCount(container_.size());
}

FTPListRemote::~FTPListRemote()
{ }

void FTPListRemote::Clear()
{
	ReInitialize(container_);
	SetItemCount(container_.size());
}

void FTPListRemote::ChangeRoot(wxString dirname)
{
	try
	{
		ScanPath(dirname);
		SetCurrectDir(dirname);
		root_ = dirname;
		root_.Trim(true);
		size_t pos = root_.Find(wxT('/'), true);
		root_ = root_.Remove(pos);
	}
	catch (const Poco::Exception& e)
	{
		throw std::runtime_error(e.displayText());
	}
}

void FTPListRemote::ScanPath(const wxString& dirname)
{
	FTPClient::Directory dir = ftpClient_->GetDir(dirname);

	ReInitialize(container_);
	for (int i = 0; i != dir.list_.size(); ++i)
	{
		Container::value_type::second_type item;
		wxString itemName(dir.list_[i].c_str(), wxConvUTF8);
		wxFileName file(itemName);
		item.isFile_ = file.HasExt() ? true : false;
		item.name_ = itemName;

		if (item.isFile_)
		{
			item.ext_ = file.GetExt();
			item.size_ = wxT("");
			item.date_ = wxT("");
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

void FTPListRemote::Connect(
	const wxString& username,
	const wxString password,
	const wxString& ipAddress,
	const int& port)
{
	ftpClient_->SetUsername(username);
	ftpClient_->SetPassword(password);

	Poco::Net::IPAddress ip(ipAddress.ToStdString(), Poco::Net::IPAddress::Family::IPv4);
	Poco::Net::SocketAddress address(ip, port);
	ftpClient_->SetAddress(address);

	root_ = ftpClient_->Connect();
	ScanPath(root_);
}

void FTPListRemote::OnActivated(wxListEvent& e)
{
	try
	{
		if (!ftpClient_->IsConnected())
			return;

		long index = e.GetIndex();
		if (index == 0)
			ChangeRoot(root_);
		else if (!container_[index].isFile_)
			ChangeRoot(container_[index].name_);
	}
	catch (const std::exception& e)
	{
		wxMessageBox(wxString(e.what()).ToStdWstring(), wxT("Error"), wxICON_ERROR);
	}
}

void FTPListRemote::OnItemSelect(wxListEvent& e)
{
	long index = e.GetIndex();
	if (index != 0)
		selectedIndex_ = index;
}

void FTPListRemote::Download(wxString dest)
{
	if (!ftpClient_->IsConnected())
		throw std::runtime_error("FTP client is not connected to the server");

	auto it = container_.find(selectedIndex_);
	if (it == container_.end())
		throw std::runtime_error("Unable to find item with given index");
	if (!it->second.isFile_)
		throw std::runtime_error("Please select file to transfer");

	dest.append(wxFileName(it->second.name_).GetFullName());
	dest.Trim(true);
	ftpClient_->Download(dest.ToStdString(), it->second.name_.ToStdString());
	//wxMessageBox(it->second.name_, wxString::Format(wxT("Downloading... to %s"), dest), wxOK | wxCENTRE, this);
}

void FTPListRemote::Upload(wxString src)
{
	if (!ftpClient_->IsConnected())
		throw std::runtime_error("FTP client is not connected to the server");

	wxString dest(GetCurrectDir());
	dest.Trim(true);
	dest.append(wxT("/") + wxFileName(src.ToStdString()).GetFullName());
	ftpClient_->Upload(dest.ToStdString(), src.ToStdString());
	//wxMessageBox(src, wxString::Format(wxT("Uploading... to %s"), GetCurrectDir()), wxOK | wxCENTRE, this);
}

void FTPListRemote::UpdateList()
{
	ChangeRoot(GetCurrectDir());
}

}
