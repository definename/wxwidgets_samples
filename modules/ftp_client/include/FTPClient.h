#pragma once

namespace ftp
{

class FTPClient
{
	//
	// Construction and destruction.
	//
public:
	//! Default constructor.
	FTPClient();
	//! Destructor.
	~FTPClient();

	//
	// Public types.
	//
public:
	//! FTP session pointer type.
	typedef Poco::SharedPtr<Poco::Net::FTPClientSession> FTPSessionPtr;
	//! Directory entry
	struct Directory
	{
		//! Directory list type.
		typedef std::vector<std::string> DirList;
		//! Directory root.
		std::string root_;
		//! Directory list.
		DirList list_;
	};

	//
	// Public interface.
	//
public:
	//! Is connected.
	bool IsConnected();
	//! Connects to the server.
	wxString Connect();
	//! Downloads.
	void Download(const std::string& dest, const std::string& source);
	//! Returns listing of current directory.
	FTPClient::Directory GetDir(const wxString& root);
	//! Uploads
	void Upload(const std::string& dest, const std::string& source);
	//! Sets username.
	void SetUsername(const wxString& username);
	//! Sets password.
	void SetPassword(const wxString& password);
	//! Sets ip address.
	void SetAddress(const Poco::Net::SocketAddress& address);

	//
	// Private interface.
	//
private:
	//! Disconnects.
	void Disconnect();


	//
	// Private data members.
	//
private:
	//! FTP server address.
	Poco::Net::SocketAddress address_;
	//! FTP session pointer.
	FTPSessionPtr ftpSession_;
	//! User password.
	wxString password_;
	//! User name.
	wxString username_;
};

} // ftp