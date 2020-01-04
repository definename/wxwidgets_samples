#pragma once

#include "pch.h"

namespace soft
{

//! Software type.
struct Software
{
	enum ARCH
	{
		x64,
		x86
	};
	//! Name.
	wxString name_;
	//! Publisher.
	wxString publisher_;
	//! Install date.
	wxString installedOn_;
	//! Size.
	wxString size_;
	//! Size.
	wxString version_;
	//! Architecture.
	ARCH arch_;
	//! Scanned by.
	wxString scannedBy_;
};

//! Software list type.
typedef std::vector<Software> SoftList;
//! Software list pointer type.
typedef std::shared_ptr<SoftList> SoftListPtr;

//! Forward declaration.
class SoftScanner;
//! Forward declaration.
class SoftListCtrl;

//! Software scanner pointer type.
typedef SoftScanner* SoftScannerPtr;
//! Software list pointer type.
typedef SoftListCtrl* SoftListCtrlPtr;

// Declares a hash map with wxString keys and wxString  values.
WX_DECLARE_STRING_HASH_MAP(wxString, SIDNameHash);

}