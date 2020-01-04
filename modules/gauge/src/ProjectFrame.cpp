#include "pch.h"
#include "ProjectFrame.h"

namespace project
{

wxBEGIN_EVENT_TABLE(ProjectFrame, wxFrame)
	EVT_CLOSE(ProjectFrame::OnCloseWindow)
	EVT_TIMER(TIMER_ID, ProjectFrame::OnTimerTimeout)
wxEND_EVENT_TABLE()

ProjectFrame::ProjectFrame()
	: wxFrame(NULL, wxID_ANY, wxT("Project"), wxDefaultPosition, wxSize(500, 100), wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX))
	, m_value(0)
{
	SetIcon(wxICON(IDI_ICON));

	m_timer = new wxTimer(this, TIMER_ID);

	//wxTimer period: 100 milliseconds
	m_timer->Start(100);
	gauge = new  wxGauge(this, wxID_ANY, 100);
}

ProjectFrame::~ProjectFrame()
{ }

void ProjectFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e))
{
	m_timer->Stop();
	Destroy();
}

void ProjectFrame::OnTimerTimeout(wxTimerEvent& event)
{
	if (m_value < 100)
	{
		//Increase wxGauge value by 1 at each timout event
		m_value++;
		gauge->SetValue(m_value);
	}
}

} // namespace project