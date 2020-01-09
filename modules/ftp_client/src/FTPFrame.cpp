#include "pch.h"
#include "FTPFrame.h"
#include "FTPPanel.h"

namespace ftp
{

//! Event table.
wxBEGIN_EVENT_TABLE(FTPFrame, wxFrame)
	EVT_CLOSE(FTPFrame::OnCloseWindow)
	EVT_MENU(ID_MENU_EXIT, FTPFrame::OnExit)
	EVT_MENU(ID_MENU_ABOUT, FTPFrame::OnAbout)
	EVT_MENU(ID_DOWNLOAD, FTPFrame::OnDownlaod)
	EVT_MENU(ID_UPLOAD, FTPFrame::OnUpload)
wxEND_EVENT_TABLE()

FTPFrame::FTPFrame()
	: wxFrame(NULL, wxID_ANY, wxT("File Transfer Protocol (FTP) Client"), wxDefaultPosition, wxSize(850, 300), wxDEFAULT_FRAME_STYLE)
	, ftpPanel_(new FTPPanel(this))
{
	SetIcon(wxICON(IDI_ICON));
	SetMinSize(GetSize());
	InitializeMenu();
}

FTPFrame::~FTPFrame()
{ }

void FTPFrame::InitializeMenu()
{
	wxMenu *menuFile = new wxMenu;
	menuFile->Append(ID_MENU_EXIT, wxT("&Exit"));
	menuFile->Append(ID_DOWNLOAD, wxT("&Download"));
	menuFile->Append(ID_UPLOAD, wxT("&Upload"));

	wxMenu *menuAbout = new wxMenu;
	menuAbout->Append(ID_MENU_ABOUT, wxT("&About"));

	wxMenuBar *menubar = new wxMenuBar;
	menubar->Append(menuFile, wxT("&File"));
	menubar->Append(menuAbout, wxT("&Help"));

	SetMenuBar(menubar);
}

void FTPFrame::OnCloseWindow(wxCloseEvent& WXUNUSED(e))
{
	Destroy();
}

void FTPFrame::OnExit(wxCommandEvent& WXUNUSED(e))
{
	Close();
}

void FTPFrame::OnAbout(wxCommandEvent& WXUNUSED(e))
{
	wxString message(wxT(
		"File transfer protocol (FTP) client\nCreated by Oleh Kolomiitsev\nKharkiv 2020\nVersion 1.0.0.2"));
	wxMessageBox(message, wxT("About"), wxOK | wxCENTRE, this);
}

void FTPFrame::OnDownlaod(wxCommandEvent& WXUNUSED(e))
{
	try
	{
		if (ftpPanel_)
			ftpPanel_->Download();
	}
	catch (const Poco::Exception& e)
	{
		wxMessageBox(wxString(e.displayText()).ToStdWstring(), wxT("Error"), wxOK | wxCENTRE, this);
	}
	catch (const std::exception& e)
	{
		wxMessageBox(wxString(e.what()).ToStdWstring(), wxT("Error"), wxOK | wxCENTRE, this);
	}
}

void FTPFrame::OnUpload(wxCommandEvent& WXUNUSED(e))
{
	try
	{
		if (ftpPanel_)
			ftpPanel_->Upload();
	}
	catch (const Poco::Exception& e)
	{
		wxMessageBox(wxString(e.displayText()).ToStdWstring(), wxT("Error"), wxOK | wxCENTRE, this);
	}
	catch (const std::exception& e)
	{
		wxMessageBox(wxString(e.what()).ToStdWstring(), wxT("Error"), wxOK | wxCENTRE, this);
	}
}

} // namespace null_app
