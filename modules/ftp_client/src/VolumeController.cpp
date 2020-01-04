#include "pch.h"
#include "Images.h"
#include "VolumeController.h"

namespace ftp
{

VolumeController::VolumeController()
{ }

VolumeController::~VolumeController()
{ }

boost::signals2::connection VolumeController::DoOnVolume(const OnVolume::slot_type& signal)
{
	return onVolume_.connect(signal);
}

void VolumeController::EnumerateVolumes(wxBoxSizer* sizer, wxWindow* parent)
{
	wxArrayString volArr = wxFSVolume::GetVolumes();
	for (const wxString& v : volArr)
	{
		wxFSVolume fs(v);
		wxString name(fs.GetName().Lower().RemoveLast());

		wxButton* btn = new wxButton(parent, wxID_ANY, name, wxPoint(0, 0), wxSize(36, 24));
		SetBtnBitmap(btn, GetBlackBitmap(fs));

		Volume vol;
		vol.btnPtr_ = btn;
		vol.fs_ = fs;
		volumes_.push_back(vol);
		btn->Bind(wxEVT_BUTTON, boost::bind(&VolumeController::OnClicked, this, _1, vol));
		sizer->Add(btn, wxSizerFlags().Proportion(0).Border(wxALL, 0));
	}
}

wxBitmap VolumeController::GetBlackBitmap(const wxFSVolume& volume) const
{
	wxBitmap icon;
	switch (volume.GetKind())
	{
	case wxFS_VOL_FLOPPY:
		icon = wxBITMAP_PNG_FROM_DATA(flash_drive);
		break;
	case wxFS_VOL_DISK:
		icon = wxBITMAP_PNG_FROM_DATA(hard_disk);
		break;
	case wxFS_VOL_CDROM:
	case wxFS_VOL_DVDROM:
		icon = wxBITMAP_PNG_FROM_DATA(compact_disc);
		break;
	case wxFS_VOL_NETWORK:
	case wxFS_VOL_OTHER:
	case wxFS_VOL_MAX:
		icon = wxBITMAP_PNG_FROM_DATA(hard_disk);
		break;
	}
	return icon;
}

wxBitmap VolumeController::GetRedBitmap(const wxFSVolume& volume) const
{
	wxBitmap icon;
	switch (volume.GetKind())
	{
	case wxFS_VOL_FLOPPY:
		icon = wxBITMAP_PNG_FROM_DATA(flash_drive_red);
		break;
	case wxFS_VOL_DISK:
		icon = wxBITMAP_PNG_FROM_DATA(hard_disk_red);
		break;
	case wxFS_VOL_CDROM:
	case wxFS_VOL_DVDROM:
		icon = wxBITMAP_PNG_FROM_DATA(compact_disc_red);
		break;
	case wxFS_VOL_NETWORK:
	case wxFS_VOL_OTHER:
	case wxFS_VOL_MAX:
		icon = wxBITMAP_PNG_FROM_DATA(hard_disk_red);
		break;
	}
	return icon;
}

VolumeController::Volume VolumeController::GetFirstVolume() const
{
	return volumes_.front();
}

void VolumeController::OnClicked(wxCommandEvent& e, const Volume& volume)
{
	try
	{
		onVolume_(volume.fs_.GetName());
		SetActiveVolume(volume);
	}
	catch (const std::exception& e)
	{
		wxMessageBox(wxString(e.what()).ToStdWstring(), wxT("Error"), wxICON_ERROR);
	}
}

void VolumeController::SetActiveVolume(const VolumeController::Volume& volume)
{
	for (const Volumes::value_type& val : volumes_)
	{
		SetBtnBitmap(val.btnPtr_, GetBlackBitmap(val.fs_));
	}

	SetBtnBitmap(volume.btnPtr_, GetRedBitmap(volume.fs_));
}

void VolumeController::SetBtnBitmap(wxButton* btn, wxBitmap bmp)
{
	btn->SetBitmap(bmp, wxLEFT);
	btn->SetBitmapPressed(bmp);
	btn->SetBitmapFocus(bmp);
	btn->SetBitmapCurrent(bmp);
}

}
