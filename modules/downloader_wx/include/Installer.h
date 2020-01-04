#pragma once

namespace downloader
{

class Installer
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
	// Public interface.
	//
public:
	//! Installs.
	void Install();
};

} // namespace downloader