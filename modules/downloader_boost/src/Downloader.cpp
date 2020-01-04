#include "pch.h"
#include "Downloader.h"

//////////////////////////////////////////////////////////////////////////
// Implementation of the Downloader class.
//

namespace downloader
{

Downloader::Downloader()
	: resolver_(ioService_)
	, socket_(ioService_)
	, stream_(new std::stringstream)
{
	Run();
}

Downloader::~Downloader()
{
	try
	{
		Stop();
	}
	catch (const std::exception&)
	{ }
}

boost::signals2::connection Downloader::DoOnCompletedSignal(const OnCompletedSignal::slot_type& signal)
{
	return onCompleted_.connect(signal);
}

boost::signals2::connection Downloader::DoOnErrorSignal(const OnErrorSignal::slot_type& signal)
{
	return onError_.connect(signal);
}

boost::signals2::connection Downloader::DoOnStartedSignal(const OnStartedSignal::slot_type& signal)
{
	return onStarted_.connect(signal);
}

Downloader::FileBuffer Downloader::GetBuffer()
{
	return stream_;
}

Downloader::DownloadType Downloader::GetType()
{
	return type_;
}

void Downloader::SetType(DownloadType type)
{
	type_ = type;
}

void Downloader::HandleResolve(
	const boost::system::error_code& err, asio::ip::tcp::resolver::iterator endpointIterator)
{
	try
	{
		if (err)
			BOOST_THROW_EXCEPTION(std::runtime_error(err.message()));
		if (!IsRunning())
			return;

		asio::async_connect(socket_, endpointIterator,
			boost::bind(&Downloader::HandleConnect, this, asio::placeholders::error));
	}
	catch (const std::exception& e)
	{
		onError_(e.what());
	}
}

void Downloader::HandleConnect(const boost::system::error_code& err)
{
	try
	{
		if (err)
			BOOST_THROW_EXCEPTION(std::runtime_error(err.message()));
		if (!IsRunning())
			return;

		asio::async_write(socket_, request_,
			boost::bind(&Downloader::HandleWriteRequest, this, asio::placeholders::error));
	}
	catch (const std::exception& e)
	{
		onError_(e.what());
	}
}

void Downloader::HandleWriteRequest(const boost::system::error_code& err)
{
	try
	{
		if (err)
			BOOST_THROW_EXCEPTION(std::runtime_error(err.message()));
		if (!IsRunning())
			return;

		asio::async_read_until(socket_, response_, "\r\n",
			boost::bind(&Downloader::HandleReadStatusLine, this, asio::placeholders::error));
	}
	catch (const std::exception& e)
	{
		onError_(e.what());
	}
}

void Downloader::HandleReadStatusLine(const boost::system::error_code& err)
{
	try
	{
		if (err)
			BOOST_THROW_EXCEPTION(std::runtime_error(err.message()));
		if (!IsRunning())
			return;

		std::istream responseStream(&response_);
		std::string httpVersion;
		responseStream >> httpVersion;
		unsigned int statusCode;
		responseStream >> statusCode;
		std::string status_message;
		std::getline(responseStream, status_message);
		if (!responseStream || httpVersion.substr(0, 5) != "HTTP/")
		{
			onError_("Invalid response");
			return;
		}
		if (statusCode != 200)
		{
			std::stringstream error;
			error << "Response returned with status code: " << statusCode;
			onError_(error.str());
			return;
		}

		asio::async_read_until(socket_, response_, "\r\n\r\n",
			boost::bind(&Downloader::HandleReadHeaders, this, asio::placeholders::error));
	}
	catch (const std::exception& e)
	{
		onError_(e.what());
	}
}

void Downloader::HandleReadHeaders(const boost::system::error_code& err)
{
	try
	{
		if (err)
			BOOST_THROW_EXCEPTION(std::runtime_error(err.message()));
		if (!IsRunning())
			return;

		std::istream response_stream(&response_);
		std::string header;
		//! Todo. Process Content-Length.
		std::vector<std::string> headers;
		while (std::getline(response_stream, header) && header != "\r")
			headers.push_back(header);

		if (response_.size() > 0)
			*stream_ << &response_;

		boost::asio::async_read(socket_, response_,
			asio::transfer_at_least(1),
			boost::bind(&Downloader::HandleReadContent, this, asio::placeholders::error));

		onStarted_();
	}
	catch (const std::exception& e)
	{
		onError_(e.what());
	}
}

void Downloader::HandleReadContent(const boost::system::error_code& err)
{
	try
	{
		if (!IsRunning())
			return;

		if (!err)
		{
			*stream_ << &response_;
			asio::async_read(socket_, response_,
				asio::transfer_at_least(1),
				boost::bind(&Downloader::HandleReadContent, this, asio::placeholders::error));
		}
		else if (err == asio::error::eof)
		{
			onCompleted_();
		}
		else
			BOOST_THROW_EXCEPTION(std::runtime_error(err.message()));

	}
	catch (const std::exception& e)
	{
		onError_(e.what());
	}
}

void Downloader::Start(
	const std::string& server,
	const std::string& port,
	const std::string& path)
{
	stream_.reset(new std::stringstream);

	std::ostream requestStream(&request_);
	requestStream << "GET " << path << " HTTP/1.1\r\n";
	requestStream << "Host: " << server << "\r\n";
	requestStream << "Accept: */*\r\n";
	requestStream << "Connection: close\r\n\r\n";

	asio::ip::tcp::resolver::query query(asio::ip::tcp::v4(), server, port);
	resolver_.async_resolve(query,
		boost::bind(&Downloader::HandleResolve, this,
		asio::placeholders::error,
		asio::placeholders::iterator));
}

void Downloader::Stop()
{
	if (!IsRunning())
		return;

	Runnable::Stop();
}

} // namespace downloader