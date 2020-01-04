#include "pch.h"
#include "SoftScanner.h"
#include "Utils.h"

namespace soft
{

SoftScanner::SoftScanner()
	: software_(new SoftList)
{ }

SoftScanner::~SoftScanner()
{
	software_->clear();
}

void SoftScanner::AddSoftware(SoftListPtr list)
{
	for (const SoftList::value_type& val : *list)
	{
		auto it = std::find_if(
			software_->begin(),
			software_->end(),
			[&val](const Software& soft) -> bool { return boost::iequals(soft.name_, val.name_); });

		if (it == software_->end())
			software_->push_back(val);
		else if (it->arch_ != val.arch_)
			software_->push_back(val);
		else if (!val.version_.IsSameAs(it->version_))
			software_->push_back(val);
		else if (!val.size_.IsSameAs(it->size_))
			software_->push_back(val);
		else if (!val.publisher_.IsSameAs(it->publisher_))
			software_->push_back(val);
	}
	list->clear();
}

SoftListPtr SoftScanner::GetScanResult() const
{
	return software_;
}

SoftListPtr SoftScanner::GetSoftwareList(
	HKEY root,
	bool is64bit,
	REGSAM samDesired,
	const wxString& owner,
	const wxString& subKey)
{
	SoftListPtr software(new SoftList);
	try
	{
		Poco::Util::WinRegistryKey key(root, subKey.ToStdString(), true, KEY_READ | samDesired);

		Poco::Util::WinRegistryKey::Keys keys;
		if (key.exists())
		{
			key.subKeys(keys);
			for (const Poco::Util::WinRegistryKey::Keys::value_type& val : keys)
			{
				std::string innerSubKey(subKey.ToStdString());
				innerSubKey.append(val);

				Poco::Util::WinRegistryKey innerKey(root, innerSubKey, true, KEY_READ | samDesired);
				if (innerKey.exists("DisplayName"))
				{
					if (innerKey.exists("SystemComponent"))
						if (GetValue(innerKey, wxT("SystemComponent")).IsSameAs(wxT("1"), false))
							continue;
					if (innerKey.exists("IsMinorUpgrade"))
						if (GetValue(innerKey, wxT("IsMinorUpgrade")).IsSameAs(wxT("1"), false))
							continue;

					//! Todo. Add RegExpretion.
					wxString displayName(GetValue(innerKey, wxT("DisplayName")));
					if (displayName.Contains(wxT("(KB")))
						continue;

					wxString installDate;
					if (innerKey.exists("InstallDate"))
						installDate = GetValue(innerKey, wxT("InstallDate"));

					wxString publisher;
					if (innerKey.exists("Publisher"))
						publisher = (GetValue(innerKey, wxT("Publisher")));

					wxString displayVersion;
					if (innerKey.exists("DisplayVersion"))
						displayVersion = GetValue(innerKey, wxT("DisplayVersion"));

					wxString estimateedSize;
					if (innerKey.exists("EstimatedSize"))
						estimateedSize = GetValue(innerKey, wxT("EstimatedSize"));

					Software soft;
					soft.name_ = displayName;
					soft.version_ = displayVersion;
					soft.installedOn_ = installDate;
					if (soft.installedOn_.empty())
					{
						wxString str = utils::QueryLastWriteTime(
							root, wxString::FromUTF8(innerSubKey.c_str()).ToStdWstring(), samDesired);
						soft.installedOn_ = str;
					}

					soft.publisher_ = publisher;
					soft.size_ = estimateedSize;
					soft.arch_ = is64bit ? Software::x64 : Software::x86;
					soft.scannedBy_ = owner;

					software->push_back(soft);
				}
			}
		}
	}
	catch (const std::exception& e)
	{
		wxMessageBox(
			wxString(wxString::Format("Unable to enumerate software: %s"),
			CU2CW(e.what())),
			wxT("Enumeration error"),
			wxICON_INFORMATION);
	}
	return software;
}

wxString SoftScanner::GetValue(Poco::Util::WinRegistryKey& key, const wxString& field)
{
	wxString value;
	if (key.exists(field.ToStdString()))
	{
		Poco::Util::WinRegistryKey::Type keyType(key.type(field.ToStdString()));
		if (keyType == Poco::Util::WinRegistryKey::REGT_STRING)
		{
			value = wxString::FromUTF8(key.getString(field.ToStdString()).c_str());
		}
		else if (keyType == Poco::Util::WinRegistryKey::REGT_STRING_EXPAND)
		{
			//! Todo. Expand environment.
			value = wxString::FromUTF8(key.getString(field.ToStdString()).c_str());
		}
		else if (keyType == Poco::Util::WinRegistryKey::REGT_DWORD)
		{
			value = wxString::Format(wxT("%i"), key.getInt(field.ToStdString()));
		}
		else if (keyType == Poco::Util::WinRegistryKey::REGT_BINARY)
		{
			std::vector<char> rawKey;
			rawKey = key.getBinary(field.ToStdString());
			if (field.IsSameAs(wxT("Sid"), false))
				value = utils::GetUserSid(rawKey);
		}
	}
	return value;
}

void SoftScanner::LoadUserSoftwareFromHKEYUsers(const SIDNameHash& sidName, bool is64bit)
{
	if (sidName.empty())
		return;

	Poco::Util::WinRegistryKey key("HKEY_USERS\\", true, KEY_READ);

	Poco::Util::WinRegistryKey::Keys keys;
	if (key.exists())
		key.subKeys(keys);

	for (const Poco::Util::WinRegistryKey::Keys::value_type& val : keys)
	{
		if (val.length() < 10)
			continue;
		SIDNameHash::const_iterator it = sidName.find(wxString::FromUTF8(val.c_str()));
		if (it == sidName.end())
			continue;

		wxString subKey(it->first);
		if (platformArch_ == wxARCH_64)
		{
			if (is64bit)
				subKey.Append(wxT("\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"));
			else
				subKey.Append(wxT("\\Software\\Wow6432Node\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"));
		}
		else if (platformArch_ == wxARCH_32)
		{
			subKey.Append(wxT("\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"));
		}
		else
		{
			continue;
		}

		SoftListPtr soft;
		soft = GetSoftwareList(
			HKEY_USERS, is64bit, 0, it->second.ToStdWstring(), subKey.ToStdString());
		AddSoftware(soft);
	}
}

SIDNameHash SoftScanner::LoadUserSoftwareFromNtUserDatFiles(bool is64bit, REGSAM samDesired)
{
	HKEY root = HKEY_LOCAL_MACHINE;
	std::string profileList = "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion\\ProfileList\\";
	Poco::Util::WinRegistryKey key(root, profileList, true, KEY_READ);

	Poco::Util::WinRegistryKey::Keys keys;
	if (key.exists())
		key.subKeys(keys);

	SIDNameHash sidName;
	for (const Poco::Util::WinRegistryKey::Keys::value_type& val : keys)
	{
		if (val.length() < 10)
			continue;

		std::string innerSubKey(profileList);
		innerSubKey.append(val);

		Poco::Util::WinRegistryKey innerKey(root, innerSubKey, true, KEY_READ);
		if (!innerKey.exists("Sid"))
			continue;
		if (!innerKey.exists("ProfileImagePath"))
			continue;

		//! We need to enumerate active user's SID.
		wxString sid = GetValue(innerKey, wxT("Sid"));
		if (sid.IsEmpty())
			continue;

		wxDir profilePath(GetValue(innerKey, "ProfileImagePath"));
		if (!wxDir::Exists(profilePath.GetNameWithSep()))
			continue;

		wxFileName profile(profilePath.GetNameWithSep());
		profile.SetFullName(wxT("ntuser.dat"));
		if (!profile.FileExists())
			continue;

		wxString username = profile.GetDirs().Last();
		sidName.insert(SIDNameHash::value_type(sid, username));

		try
		{
			std::wstring hive(L"INVENTORY");
			wxString subKey(hive);
			subKey.Append(wxT("\\Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"));

			//! Todo. Implement RAII.
			utils::LoadKey(HKEY_LOCAL_MACHINE, hive, profile.GetFullPath(wxPATH_WIN).ToStdWstring());

			SoftListPtr soft;
			soft = GetSoftwareList(
				HKEY_LOCAL_MACHINE, is64bit, samDesired, username, subKey.ToStdString());
			AddSoftware(soft);

			utils::UnloadKey(HKEY_LOCAL_MACHINE, hive);
		}
		catch (const std::exception& e)
		{
			std::stringstream errorStream;
			errorStream << wxString(wxString::Format(
				"Unable to load data from the %s's registry hive: %s", username.ToStdString(), e.what()));
			std::wstring error = CU2CW(errorStream.str());

			wxMessageBox(error, wxT("Registry loading error"), wxICON_INFORMATION);
		}
	}

	return sidName;
}

void SoftScanner::LoadUserSoftwareList(bool is64bit, REGSAM samDesired)
{
	SIDNameHash sids = LoadUserSoftwareFromNtUserDatFiles(is64bit, samDesired);
	LoadUserSoftwareFromHKEYUsers(sids, is64bit);
}

void SoftScanner::Scan()
{
	try
	{
		platformArch_ = wxPlatformInfo().GetArchitecture();
		if (platformArch_ == wxARCH_64)
		{
			SoftListPtr soft;

			soft = GetSoftwareList(HKEY_LOCAL_MACHINE, true, KEY_WOW64_64KEY, wxT("Machine"), wxT("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"));
			AddSoftware(soft);

			LoadUserSoftwareList(true, KEY_WOW64_64KEY);

			soft = GetSoftwareList(HKEY_LOCAL_MACHINE, false, KEY_WOW64_32KEY, wxT("Machine"), wxT("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"));
			AddSoftware(soft);

			LoadUserSoftwareList(false, KEY_WOW64_32KEY);
		}
		else if (platformArch_ == wxARCH_32)
		{
			SoftListPtr soft;
			soft = GetSoftwareList(HKEY_LOCAL_MACHINE, false, 0, wxT("Machine"), wxT("Software\\Microsoft\\Windows\\CurrentVersion\\Uninstall\\"));
			AddSoftware(soft);

			LoadUserSoftwareList(false, 0);
		}
		else
		{
			throw std::runtime_error("OS architecture error");
		}

		std::sort(
			software_->begin(),
			software_->end(),
			[](const SoftList::value_type& f, const SoftList::value_type& s) -> bool
		{
			return boost::algorithm::ilexicographical_compare(f.name_, s.name_, std::locale());
		});
	}
	catch (const std::exception& e)
	{
		wxMessageBox(
			wxString(wxString::Format("Scanner error: %s"),
			CU2CW(e.what())),
			wxT("Scanner error"),
			wxICON_INFORMATION);
	}
}


}