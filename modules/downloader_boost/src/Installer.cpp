#include "pch.h"
#include "Installer.h"
#include "ProjectApp.h"

//////////////////////////////////////////////////////////////////////////
// Implementation of the Downloader class.
//

namespace downloader
{

Installer::Installer()
{
	Run();
}

Installer::~Installer()
{
	try
	{
		Stop();
	}
	catch (const std::exception&)
	{ }
}

boost::signals2::connection Installer::DoOnCompletedSignal(const OnCompletedSignal::slot_type& signal)
{
	return onComplete_.connect(signal);
}

boost::signals2::connection Installer::DoOnErrorSignal(const OnErrorSignal::slot_type& signal)
{
	return onError_.connect(signal);
}

void Installer::DoInstall(const boost::filesystem::path& msiPath)
{
	try
	{
		BOOST_SCOPE_EXIT(&msiPath)
		{
			boost::filesystem::remove(msiPath);
		}
		BOOST_SCOPE_EXIT_END

		wxString args(wxString::Format(wxT(" /%s /norestart TRAY_MODE=%s")
		, (wxGetApp().IsSilentMode() ? wxT("qn") : wxT("qb"))
		, (wxGetApp().IsNoTrayMode() ? wxT("notray") : wxT("install"))));

// 		std::wstring args = boost::str(boost::wformat(
// 			//L" /%s /norestart TRAY_MODE=%s ONETIME_MODE=%s ONETIME_ID=%s")
// 			L" /%s /norestart TRAY_MODE=%s")
// 			% (wxGetApp().IsSilentMode() ? L"qn" : L"qb")
// 			% (wxGetApp().IsNoTrayMode() ? L"notray" : L"install")
// 			//% (oneTimeSettings.isOneTime_ ? L"onetime" : L"manytimes")
// 			//% uuids::to_wstring(oneTimeSettings.sessionId_)
// 			);

		SHELLEXECUTEINFO info;
		ZeroMemory(&info, sizeof(SHELLEXECUTEINFO));
		info.cbSize = sizeof(SHELLEXECUTEINFO);
		info.fMask = SEE_MASK_NOCLOSEPROCESS;
		info.nShow = wxGetApp().IsSilentMode() ? SW_HIDE : SW_NORMAL;
		info.lpVerb = L"open";
		info.lpFile = msiPath.wstring().c_str();
		info.lpParameters = args.ToStdWstring().c_str();

		CHECK_OS_ERROR(::ShellExecuteExW(&info));
		CHECK_OS_ERROR(::WaitForSingleObject(info.hProcess, INFINITE) == WAIT_OBJECT_0);
		CHECK_OS_ERROR(::CloseHandle(info.hProcess));

		onComplete_();
	}
	catch (const std::exception& e)
	{
		onError_(e.what());
	}
}

void Installer::Stop()
{
	if (!IsRunning())
		return;

	Runnable::Stop();
}

void Installer::Install(const boost::filesystem::path& msiPath)
{
	if (IsRunning())
		ioService_.post(boost::bind(&Installer::DoInstall, this, msiPath));
}

} // namespace downloader