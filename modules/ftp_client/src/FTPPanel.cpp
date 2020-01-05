#include "pch.h"
#include "FTPListLocal.h"
#include "FTPListRemote.h"
#include "FTPPanel.h"
#include "Images.h"
#include "SplitterWindow.h"
#include "TextControl.h"
#include "VolumeController.h"

namespace ftp
{

wxBEGIN_EVENT_TABLE(FTPPanel, wxPanel)
	EVT_BUTTON(wxID_ANY, FTPPanel::OnLogin)
wxEND_EVENT_TABLE()

FTPPanel::FTPPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY, wxDefaultPosition, parent->GetSize())
	, ip_(new TextControl(this))
	, password_(new TextControl(this, wxTE_PASSWORD))
	, port_(new TextControl(this, wxTE_CENTRE))
	, username_(new TextControl(this))
	, volumeController_(new VolumeController())
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	InitializePanel(topSizer);
	InitializeSplitter(topSizer);

	SetSizer(topSizer);
}

FTPPanel::~FTPPanel()
{ }

void FTPPanel::Download()
{
	//! Todo. Do it in a separate thread.
	listRemote_->Download(listLocal_->GetCurrectDir());
	listLocal_->UpdateList();
}

void FTPPanel::Upload()
{
	//! Todo. Do it in a separate thread.
	listRemote_->Upload(listLocal_->GetSelectedFile());
	listRemote_->UpdateList();
}

void FTPPanel::InitializePanel(wxBoxSizer* sizer)
{
	wxFlexGridSizer* flexSizer = new wxFlexGridSizer(1, 2, 0, 0);
	flexSizer->AddGrowableCol(0);
	flexSizer->AddGrowableCol(1);

	wxBoxSizer* leftSizer = new wxBoxSizer(wxHORIZONTAL);
	btnLogin_ = new wxBitmapButton(
		this,
		IDs::ID_CONNECT,
		wxBITMAP_PNG_FROM_DATA(lightning_yellow_16),
		wxPoint(0, 0),
		wxSize(24, 24)/*, wxBORDER_NONE | wxBU_NOTEXT*/);
	leftSizer->Add(btnLogin_, wxSizerFlags().Proportion(0).Border(wxALL, 0));

	ip_->SetHint(wxT("Host"));
	ip_->SetSize(wxSize(150, 22));
	//! Todo. Remove default value.
	ip_->SetValue(wxT("178.150.81.242"));
	leftSizer->Add(ip_, wxSizerFlags().Proportion(0).FixedMinSize().CenterVertical().Border(wxRIGHT, 1));

	username_->SetHint(wxT("Username"));
	username_->SetSize(wxSize(150, 22));
	//! Todo. Remove default value.
	username_->SetValue(wxT("definename"));
	leftSizer->Add(username_, wxSizerFlags().Proportion(0).FixedMinSize().CenterVertical().Border(wxRIGHT, 1));

	password_->SetHint(wxT("Password"));
	password_->SetSize(wxSize(150, 22));
	//! Todo. Remove default value.
	password_->SetValue(wxT("definepassword"));
	leftSizer->Add(password_, wxSizerFlags().Proportion(0).FixedMinSize().CenterVertical().Border(wxRIGHT, 1));

	port_->SetHint(wxT("Port"));
	//! Todo. Remove default value.
	port_->SetValue(wxT("21"));
	port_->SetSize(wxSize(40, 22));
	leftSizer->Add(port_, wxSizerFlags().Proportion(0).FixedMinSize().CenterVertical().Border(wxRIGHT, 1));

	flexSizer->Add(leftSizer, wxSizerFlags().Proportion(0).Left().Border(wxALL, 0));

	wxBoxSizer* rightSizer = new wxBoxSizer(wxHORIZONTAL);
	volumeController_->EnumerateVolumes(rightSizer, this);

	flexSizer->Add(rightSizer, wxSizerFlags().Proportion(0).Right().Border(wxALL, 0));

	sizer->Add(flexSizer, wxSizerFlags().Proportion(0).Expand().Border(wxALL, 0));
}

void FTPPanel::InitializeSplitter(wxBoxSizer* sizer)
{
	SplitterWindowPtr vSplitter = new SplitterWindow(this);
	vSplitter->SetSashGravity(0.5);

	listRemote_ = new FTPListRemote(vSplitter);
	listLocal_ = new FTPListLocal(vSplitter);

	VolumeController::Volume vol = volumeController_->GetFirstVolume();
	volumeController_->SetActiveVolume(vol);

	try
	{
		listLocal_->ChangeRoot(vol.fs_.GetName());
	}
	catch (const std::exception& e)
	{
		wxMessageBox(wxString(e.what()).ToStdWstring(), wxT("Error"), wxICON_ERROR);
	}

	volumeController_->SetVolumeCb(std::bind(&FTPListLocal::ChangeRoot, listLocal_, std::placeholders::_1));

	vSplitter->SplitVertically(listRemote_, listLocal_, 0);
	sizer->Add(vSplitter, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 0));
}

void FTPPanel::OnLogin(wxCommandEvent& e)
{
	int btnId = e.GetId();
	if (btnId == IDs::ID_CONNECT)
	{
		try
		{
			if (ip_->IsEmpty())
				throw std::runtime_error("Empty address");
			if (username_->IsEmpty())
				throw std::runtime_error("Empty username");
			if (password_->IsEmpty())
				throw std::runtime_error("Empty password");
			if (port_->IsEmpty())
				throw std::runtime_error("Empty port");

			wxString username, password, ip;
			short port;
			ip = ip_->GetValue();
			port = wxAtoi(port_->GetValue());
			username = username_->GetValue();
			password = password_->GetValue();

			listRemote_->Connect(username, password, ip, port);
			btnLogin_->SetBitmap(wxBITMAP_PNG_FROM_DATA(lightning_red_16));
		}
		catch (const std::exception& e)
		{
			listRemote_->Clear();
			btnLogin_->SetBitmap(wxBITMAP_PNG_FROM_DATA(lightning_yellow_16));
			wxMessageBox(wxString(e.what()).ToStdWstring(), wxT("Info"), wxICON_INFORMATION);
		}
	}
}

} // namespace null_app
