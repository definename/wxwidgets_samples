#pragma once

#include "Runnable.h"

//////////////////////////////////////////////////////////////////////////
// Interface of the Installer class.
//

namespace downloader
{

class Installer : public Runnable
{
	//
	// Construction and destruction.
	//
public:
	//! Constructor.
	Installer();
	//! Destructor.
	~Installer();

	//
	// Public types.
	//
public:
	//! OnError signal type.
	typedef boost::signals2::signal<void(const std::string&)> OnErrorSignal;
	//! OnCompleted signal type.
	typedef boost::signals2::signal<void()> OnCompletedSignal;

	//
	// Public interface.
	//
public:
	//! Sets error signal.
	boost::signals2::connection DoOnErrorSignal(const OnErrorSignal::slot_type& signal);
	//! Sets completed signal.
	boost::signals2::connection DoOnCompletedSignal(const OnCompletedSignal::slot_type& signal);
	//! Stops installer.
	void Stop();
	//! Installs.
	void Install(const boost::filesystem::path& msiPath);

	//
	// Private interface.
	//
private:
	//! Do install.
	void DoInstall(const boost::filesystem::path& msiPath);

	//
	// Private data members.
	//
private:
	//! Error signal.
	OnErrorSignal onError_;
	//! Complete signal.
	OnCompletedSignal onComplete_;
};

} // namespace downloader