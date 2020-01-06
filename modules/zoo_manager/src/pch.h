#pragma once

//////////////////////////////////////////////////////////////////////////
// Stl includes and definitions.
//

#include <fstream>
#include <memory>

//////////////////////////////////////////////////////////////////////////
// Boost includes and definitions.
//

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/unordered_map.hpp>

//////////////////////////////////////////////////////////////////////////
// wxWidgets includes and definitions.
//
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/textctrl.h>
#include <wx/hashmap.h>
#include <wx/sharedptr.h>

// #include "wx/filename.h"
// #include <wx/textctrl.h>
// #include <wx/splitter.h>
// #include <wx/volume.h>
// #include <wx/dir.h>
// #include <wx/artprov.h>
// #include <wx/mimetype.h>