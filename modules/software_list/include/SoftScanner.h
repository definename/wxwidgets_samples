#pragma once

#include "Types.h"

namespace soft
{

class SoftScanner
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	SoftScanner();
	//! Destructor.
	~SoftScanner();

	//
	// Public interface
	//
public:
	//! Returns scan result.
	SoftListPtr GetScanResult() const;
	//! Scans.
	void Scan();

	//
	// Private interface.
	//
private:
	//! Adds software.
	void AddSoftware(SoftListPtr list);
	//! Get Windows software list.
	SoftListPtr GetSoftwareList(
		HKEY root,
		bool is64bit,
		REGSAM samDesired,
		const wxString& owner,
		const wxString& subKey);
	//! Returns registry value.
	wxString GetValue(Poco::Util::WinRegistryKey& key, const wxString& field);
	//! Load user's software from HKEY Users.
	void LoadUserSoftwareFromHKEYUsers(const SIDNameHash& sidName, bool is64bit);
	//! Load user's software from ntuser.dat file.
	SIDNameHash LoadUserSoftwareFromNtUserDatFiles(bool is64bit, REGSAM samDesired);
	//! Loads user software list.
	void LoadUserSoftwareList(bool is64bit, REGSAM samDesired);

	//
	// Private data members.
	//
private:
	//! Scanned software list.
	SoftListPtr software_;
	//! Sub key.
	const std::string subKey_;
	//! Platform architecture.
	wxArchitecture platformArch_;
};

}