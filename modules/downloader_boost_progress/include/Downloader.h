#pragma once

#include "Runnable.h"

//////////////////////////////////////////////////////////////////////////
// Interface of the Downloader class.
//

namespace downloader
{

class Downloader : public Runnable
{
public:
	//! Constructor.
	Downloader();
	//! Destructor.
	~Downloader();

	//
	// Public types.
	//
public:
	//! Download type.
	enum DownloadType
	{
		DownloadFileVersion,
		DownloadInstaller
	};
	//! Headers container type.
	typedef std::map<std::string, std::string> Headers;
	//! OnCompleted signal type.
	typedef boost::signals2::signal<void()> OnCompletedSignal;
	//! OnError signal type.
	typedef boost::signals2::signal<void(const std::string&)> OnErrorSignal;
	//! OnProgress signal type.
	typedef boost::signals2::signal<void()> OnProgressSignal;
	//! OnStarted signal type.
	typedef boost::signals2::signal<void()> OnStartedSignal;
	//! file buffer type.
	typedef std::shared_ptr<std::stringstream> FileBuffer;

	//
	// Public interface.
	//
public:
	//! Sets completed signal.
	boost::signals2::connection DoOnCompletedSignal(const OnCompletedSignal::slot_type& signal);
	//! Sets error signal.
	boost::signals2::connection DoOnErrorSignal(const OnErrorSignal::slot_type& signal);
	//! Sets started signal.
	boost::signals2::connection DoOnProgressSignal(const OnProgressSignal::slot_type& signal);
	//! Sets started signal.
	boost::signals2::connection DoOnStartedSignal(const OnStartedSignal::slot_type& signal);
	//! Returns file stream.
	FileBuffer GetBuffer();
	//! Gets downloading type.
	DownloadType GetType();
	//! Sets downloading type.
	void SetType(DownloadType type);
	//! Starts downloading.
	void Start(
		const std::string& server,
		const std::string& port,
		const std::string& path);
	//! Stops downloader.
	void Stop();


	//
	// Private interface.
	//
private:
	//! Handles resolve.
	void HandleResolve(
		const boost::system::error_code& err, asio::ip::tcp::resolver::iterator endpointIterator);
	//! Handles connect.
	void HandleConnect(const boost::system::error_code& err);
	//! Handles write request.
	void HandleWriteRequest(const boost::system::error_code& err);
	//! Handles status line.
	void HandleReadStatusLine(const boost::system::error_code& err);
	//! Handles headers.
	void HandleReadHeaders(const boost::system::error_code& err);
	//! Handles content.
	void HandleReadContent(const boost::system::error_code& err);

	//
	// Private data members.
	//
private:
	//! HTTP headers container.
	Headers headers_;
	//! TCP resolver.
	asio::ip::tcp::resolver resolver_;
	//! Socket.
	asio::ip::tcp::socket socket_;
	//! Request buffer.
	boost::asio::streambuf request_;
	//! Response buffer.
	boost::asio::streambuf response_;
	//! Destination file.
	FileBuffer stream_;
	//! Completed signal.
	OnCompletedSignal onCompleted_;
	//! Error signal.
	OnErrorSignal onError_;
	// Started signal.
	OnStartedSignal onStarted_;
	//! Progress signal.
	OnProgressSignal onProgress_;
	//! Percentage of the received file.
	int percentage_;
	//! Download type.
	DownloadType type_;
};

} // namespace downloader