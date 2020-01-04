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
	//! Volumes container type.
	typedef std::list<Volume> Volumes;
	//! OnVolume signal type.
	typedef boost::signals2::signal<void(const wxString&)> OnVolume;

	//
	// Public interface.
	//
public:
	//! Sets OnVolume signal.
	boost::signals2::connection DoOnVolume(const OnVolume::slot_type& signal);
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
	//! On volume signal.
	OnVolume onVolume_;
};

};