#include "pch.h"
#include "FTPClient.h"

namespace ftp
{

FTPClient::FTPClient()
	: ftpSession_(new Poco::Net::FTPClientSession())
{ }

FTPClient::~FTPClient()
{
	try
	{
		Disconnect();
	}
	catch (const std::exception&/* e*/)
	{ }
}

void FTPClient::SetUsername(const wxString& username)
{
	username_ = username;
}

void FTPClient::SetPassword(const wxString& password)
{
	password_ = password;
}

void FTPClient::SetAddress(const Poco::Net::SocketAddress& address)
{
	address_ = address;
}

FTPClient::Directory FTPClient::GetDir(const wxString& root)
{
	Directory dir;
	std::istream& is = ftpSession_->beginList(root.ToUTF8().data(), false);

	if (!dir.list_.empty())
		dir.list_.clear();

	std::string path;
	while (std::getline(is, path))
	{
		dir.list_.push_back(path);
	}

	ftpSession_->endList();

	return dir;
}

wxString FTPClient::Connect()
{
	try
	{
		Disconnect();

		ftpSession_->setPassive(true);
		ftpSession_->open(address_.host().toString(), address_.port());
		ftpSession_->login(username_.ToStdString(), password_.ToStdString());
	}
	catch (const Poco::Exception& e)
	{
		throw std::runtime_error(e.displayText());
	}

	return wxString(ftpSession_->getWorkingDirectory());
}

void FTPClient::Download(const std::string& dest, const std::string& src)
{
	//! Todo. Is it possible to use paths as wide string?
	std::ofstream ofstr;
	ofstr.open(dest.c_str(), std::ofstream::out | std::ofstream::binary);
	if (!ofstr.is_open())
		throw std::runtime_error("Unable to open destination file");

	std::istream& istr = ftpSession_->beginDownload(src);
	Poco::StreamCopier::copyStreamUnbuffered(istr, ofstr);
	ftpSession_->endDownload();
}

void FTPClient::Upload(const std::string& dest, const std::string& src)
{
	//! Todo. Is it possible to use paths as wide string?
	std::ifstream ifstr;
	ifstr.open(src.c_str(), std::ofstream::in | std::ofstream::binary);
	if (!ifstr.is_open())
		throw std::runtime_error("Unable to open source file");

	std::ostream& ostr = ftpSession_->beginUpload(dest);
	Poco::StreamCopier::copyStreamUnbuffered(ifstr, ostr);
	ftpSession_->endUpload();
}

void FTPClient::Disconnect()
{
	if (ftpSession_->isLoggedIn())
		ftpSession_->logout();
	if (ftpSession_->isOpen())
		ftpSession_->close();
}

bool FTPClient::IsConnected()
{
	if (!ftpSession_->isLoggedIn() || !ftpSession_->isOpen())
		return false;

	return true;
}

} // ftp