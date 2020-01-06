#pragma once

namespace zoo
{

class ZooAddPanel: public wxPanel
{
	// Construction and destruction.
public:
	//! Constructor.
	ZooAddPanel(wxWindow* parent);
	//! Destructor.
	~ZooAddPanel();

	// Public types.
public:
	//! Command id type.
	enum class CommandId : int
	{
		ID_NAME = 0,
		ID_GENDER,
		ID_AGE,
		ID_CELL
	};
};

}; // namespace zoo