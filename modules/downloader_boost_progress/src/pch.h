#pragma once

//////////////////////////////////////////////////////////////////////////
// Boost includes and definitions.
//

#include <boost/property_tree/ini_parser.hpp>
#include <boost/thread/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem.hpp>
#include <boost/exception/all.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/signals2.hpp>
#include <boost/scope_exit.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/config/warning_disable.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#include <boost/spirit/include/qi.hpp>

namespace asio = boost::asio;
namespace fs = boost::filesystem;
namespace ptree = boost::property_tree;

//////////////////////////////////////////////////////////////////////////
// wxWidgets includes and definitions.
//
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/activityindicator.h>
#include <wx/stattext.h>
#include <wx/sharedptr.h>
#include <wx/uri.h>
#include <wx/platinfo.h>
#include <wx/cmdline.h>

#include <wx/string.h>

//////////////////////////////////////////////////////////////////////////
// Platform specific includes and definitions.
//

#include <Shellapi.h>

//////////////////////////////////////////////////////////////////////////
// Libaim includes and definitions.
//

#include "libaim/platform.h"

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <map>