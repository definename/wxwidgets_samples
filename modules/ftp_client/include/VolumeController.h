#pragma once

namespace ftp
{

class VolumeController
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	VolumeController();
	//! Destructor.
	~VolumeController();

	//
	// Public types.
	//
public:
	//! Volume type.
	struct Volume
	{
		wxFSVolume fs_;
		wxButton* btnPtr_;
	};
	//! Volume container type.
	using Volumes = std::list<Volume>;
	//! OnVolume signal type.
	using VolumeCb = std::function<void(const wxString&)>;

	//
	// Public interface.
	//
public:
	//! Sets volume cb.
	void SetVolumeCb(const VolumeCb& volumeCb);
	//! Enumerates volumes.
	void EnumerateVolumes(wxBoxSizer* sizer, wxWindow* parent);
	//! Returns first volume.
	Volume GetFirstVolume() const;
	//! Sets button to active bitmap.
	void SetActiveVolume(const VolumeController::Volume& volume);


	//
	// Private interface.
	//
private:
	//! Returns black bitmap.
	wxBitmap GetBlackBitmap(const wxFSVolume& volume) const;
	//! Returns red bitmap.
	wxBitmap GetRedBitmap(const wxFSVolume& volume) const;
	//! On button clicked event handler.
	void OnClicked(wxCommandEvent& e, const Volume& volume);
	//! Sets button's bitmap.
	void SetBtnBitmap(wxButton* btn, wxBitmap bmp);

	//
	// Private data members.
	//
private:
	//! Volumes container.
	Volumes volumes_;
	//! Volume cb.
	VolumeCb volumeCb_;
};

};