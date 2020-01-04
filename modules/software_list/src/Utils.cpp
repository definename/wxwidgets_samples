#include "pch.h"
#include "Utils.h"

namespace soft
{
namespace utils
{

wxString GetUserSid(std::vector<char>& rawSid)
{
	LPTSTR sid = NULL;

	BOOST_SCOPE_EXIT(sid)
	{
		::LocalFree(sid);
	}
	BOOST_SCOPE_EXIT_END;

	::ConvertSidToStringSid(reinterpret_cast<PSID>(&rawSid[0]), &sid);

	return sid;
}

wxString QueryLastWriteTime(HKEY hKey, const std::wstring& subKey, REGSAM samDesired)
{
	HKEY key;
	if (::RegOpenKeyEx(hKey, subKey.c_str(), 0, KEY_READ | samDesired, &key) == ERROR_SUCCESS)
	{
		FILETIME ft;
		if (::RegQueryInfoKey(
			key, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, &ft) == ERROR_SUCCESS)
		{
			SYSTEMTIME st;
			if (::FileTimeToSystemTime(&ft, &st) != 0)
			{
				wxDateTime dt;
				dt.SetFromMSWSysTime(st);

				RegCloseKey(key);
				return dt.Format(wxT("%Y%m%d"));
			}
		}
	}

	RegCloseKey(key);
	return wxString();
}

void LoadKey(HKEY hKey, const _tstring& subKey, const _tstring& file)
{
	HANDLE hToken = NULL;
	CHECK_OS_ERROR(::OpenProcessToken(GetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken));

	SetPrivilege(hToken, SE_BACKUP_NAME, TRUE);
	SetPrivilege(hToken, SE_RESTORE_NAME, TRUE);
	::CloseHandle(hToken);

	CHECK_REG_ERROR(::RegLoadKey(hKey, subKey.c_str(), file.c_str()));
}

void UnloadKey(HKEY hKey, const _tstring& subKey)
{
	CHECK_REG_ERROR(::RegUnLoadKey(hKey, subKey.c_str()));
}

void SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege)
{
	LUID luid;
	CHECK_OS_ERROR(::LookupPrivilegeValue(NULL, lpszPrivilege, &luid));

	TOKEN_PRIVILEGES tp;
	tp.PrivilegeCount = 1;
	tp.Privileges[0].Luid = luid;

	if (bEnablePrivilege)
		tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	else
		tp.Privileges[0].Attributes = 0;

	CHECK_OS_ERROR(::AdjustTokenPrivileges(
		hToken,
		FALSE,
		&tp,
		sizeof(TOKEN_PRIVILEGES),
		reinterpret_cast<PTOKEN_PRIVILEGES>(NULL),
		reinterpret_cast<PDWORD>(NULL)));
}

}
}