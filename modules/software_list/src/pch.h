#pragma once

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <vector>

#ifdef _UNICODE
#define _tcout std::wcout
#define _tcin std::wcin
#define _tcerr std::wcerr
#define _tstring std::wstring
#define _tostream std::wostream
#define _tistream std::wistream
#define _tstringstream std::wstringstream
#define _tostringstream std::wostringstream
#define _tistringstream std::wistringstream
#else
#define _tcin std::cin
#define _tcout std::cout
#define _tcerr std::cerr
#define _tstring std::string
#define _tostream std::ostream
#define _tistream std::istream
#define _tstringstream std::stringstream
#define _tostringstream std::ostringstream
#define _tistringstream std::istringstream
#endif

//////////////////////////////////////////////////////////////////////////
// Platform specific includes and definitions.
//

#include <windows.h>
#include <Sddl.h>

//////////////////////////////////////////////////////////////////////////
// wxWidgets includes and definitions.
//

#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "wx/listctrl.h"
#include "wx/filename.h"
#include "wx/dir.h"
#include "wx/hashmap.h"

//////////////////////////////////////////////////////////////////////////
// Poco includes and definitions
//

#define POCO_NO_UNWINDOWS

#include "Poco/Foundation.h"
#include "Poco/Util/WinRegistryKey.h"

//////////////////////////////////////////////////////////////////////////
// Boost includes and definition.
//

#include "boost/algorithm/string.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/scope_exit.hpp"

//////////////////////////////////////////////////////////////////////////
// libaim includes and definitions.
//

#include "libaim/except.h"
#include "libaim/common.h"