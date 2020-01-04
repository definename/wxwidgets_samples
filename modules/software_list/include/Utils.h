#pragma once

namespace soft
{
namespace utils
{

//! Query last write time.
wxString QueryLastWriteTime(HKEY hKey, const std::wstring& subKey, REGSAM samDesired);
//! Load key.
void LoadKey(HKEY hKey, const _tstring& subKey, const _tstring& file);
//! Unloads key.
void UnloadKey(HKEY hKey, const _tstring& subKey);
//! Sets privilege.
void SetPrivilege(HANDLE hToken, LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);
//! Returns user's SID.
wxString GetUserSid(std::vector<char>& rawSid);

}
}