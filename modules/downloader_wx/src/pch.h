#pragma once

//////////////////////////////////////////////////////////////////////////
// wxWidgets includes and definitions.
//
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/activityindicator.h>
#include <wx/stattext.h>
#include <wx/url.h>
#include <wx/wfstream.h>
#include <wx/sharedptr.h>
#include <wx/thread.h>


//////////////////////////////////////////////////////////////////////////
// Boost includes and definition.
//

#include "boost/exception/all.hpp"
#include "boost/filesystem.hpp"

namespace fs = boost::filesystem;