#pragma once

//////////////////////////////////////////////////////////////////////////
// STL includes and definitions.
//

#include <fstream>
#include <memory>
#include <algorithm>

//////////////////////////////////////////////////////////////////////////
// Boost includes and definitions.
//

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/shared_ptr.hpp>

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
#include <wx/filename.h>