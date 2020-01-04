#include "pch.h"
#include "DownloadThread.h"
#include "DownloadFrame.h"

namespace downloader
{

DownloadThread::DownloadThread(DownloadFrame* owner, wxURL& url)
	: wxThread(wxTHREAD_DETACHED)
	, ownerPtr_(owner)
	, url_(url)
{ }

DownloadThread::~DownloadThread()
{
	wxCriticalSectionLocker enter(ownerPtr_->dtCriticalSection_);
	ownerPtr_->downloadThread_ = NULL;
}

ssize_t DownloadThread::CopyStreamUnbuffered(wxInputStream& istr, wxOutputStream& ostr)
{
	wxChar c;
	ssize_t len = 0;
	c = istr.GetC();
	while (istr.IsOk() && ostr.IsOk())
	{
		if (TestDestroy())
			break;

		++len;
		ostr.PutC(c);
		c = istr.GetC();
	}
	return len;
}

void DownloadThread::Download(wxURL& url, fs::path dest)
{
	fs::path temp = dest;
	temp.replace_extension(wxT("downloading"));

	if (url.GetError() != wxURL_NOERR)
		BOOST_THROW_EXCEPTION(std::runtime_error("URL error occurred"));

	wxSharedPtr<wxInputStream> iStream;
	iStream.reset(url.GetInputStream());
	if (!iStream || !iStream->IsOk())
		BOOST_THROW_EXCEPTION(std::runtime_error("Invalid input stream"));

	wxFile file(temp.wstring(), wxFile::write);
	if (!file.IsOpened())
		BOOST_THROW_EXCEPTION(std::runtime_error("Unable to create file: " + temp.string()));
	wxFileOutputStream fileStream(file);
	if (!fileStream.IsOk())
		BOOST_THROW_EXCEPTION(std::runtime_error("Invalid output file stream"));

	CopyStreamUnbuffered(*iStream, fileStream);

	fileStream.Close();
	file.Close();

	fs::rename(temp, dest);
}

wxThread::ExitCode DownloadThread::Entry()
{
	try
	{
		fs::path dest(wxT("D://file.msi"));
		Download(url_, dest);
		QueueEvent(new wxCommandEvent(wxEVT_COMMAND_DOWNLOADTHREAD_COMPLETED));
	}
	catch (const std::exception& e)
	{
		QueueEvent(new wxCommandEvent(wxEVT_COMMAND_DOWNLOADTHREAD_COMPLETED), e.what());
	}

	return wx_static_cast(wxThread::ExitCode, 0);
}

void DownloadThread::QueueEvent(wxCommandEvent* e, const wxString& s/* = wxT("")*/)
{
	e->SetString(s);
	wxQueueEvent(ownerPtr_, e);
}

} // namespace downloader