#pragma once

namespace project
{

class ProjectFrame : public wxFrame
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	ProjectFrame();
	//! Destructor.
	~ProjectFrame();

	//
	// Public types.
	//
public:
	//! Timer pointer type.
	typedef wxTimer* TimerPtr;
	//! Gauge pointer type.
	typedef wxGauge* GaugePtr;
	//! Timer id.
	enum
	{
		TIMER_ID = 10
	};

	//
	// Private interface.
	//
private:
	//! On close event handler.
	void OnCloseWindow(wxCloseEvent& WXUNUSED(e));
	//! Handler timer timeout.
	void OnTimerTimeout(wxTimerEvent& event);
	// Any class wishing to process wxWidgets events must use this macro.
	wxDECLARE_EVENT_TABLE();

	//
	// Private data members.
	//
private:
	TimerPtr m_timer;
	double m_value;
	GaugePtr gauge;
};

} // namespace project