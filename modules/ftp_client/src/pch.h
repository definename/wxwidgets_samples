#pragma once

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <list>
#include <map>
#include <fstream>

//////////////////////////////////////////////////////////////////////////
// Boost includes and definitions.
//

#include "boost/bind.hpp"
#include "boost/signals2.hpp"

//////////////////////////////////////////////////////////////////////////
// Poco includes and definitions.
//

#define POCO_NO_UNWINDOWS

#include "Poco/Foundation.h"
#include "Poco/Net/FTPClientSession.h"
#include "Poco/StreamCopier.h"

//////////////////////////////////////////////////////////////////////////
// wxWidgets includes and definitions.
//
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include "wx/filename.h"
#include <wx/listctrl.h>
#include <wx/textctrl.h>
#include <wx/splitter.h>
#include <wx/volume.h>
#include <wx/dir.h>
#include <wx/artprov.h>
#include <wx/mimetype.h>