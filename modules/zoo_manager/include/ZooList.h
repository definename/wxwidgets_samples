#pragma once

namespace zoo
{

class ZooList: public wxListCtrl
{
	// Construction and destruction.
public:
	//! Constructor.
	ZooList(wxWindow* parent);
	//! Destructor.
	~ZooList();
};

}; // namespace zoo