#pragma once

namespace zoo
{

struct ZooData
{
	// Construction and destruction.
public:
	// Constructor.
	ZooData(wxString name, wxString gender, wxString age, wxString cell)
		: name_(name)
		, gender_(gender)
		, age_(age)
		, cell_(cell) {
	}

	// Public types.
public:
	// Animal name.
	wxString name_;
	// Animal gender.
	wxString gender_;
	// Animal age.
	wxString age_;
	// Animal cell.
	wxString cell_;
};

// Zoo data pointer type.
using ZooDataPtr = wxSharedPtr<ZooData>;

}; // namespace zoo