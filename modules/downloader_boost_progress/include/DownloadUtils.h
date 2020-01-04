#pragma once

namespace downloader
{
namespace utils
{

//! Parses installer link.
std::string ParseInstallerLink(std::shared_ptr<std::stringstream> stream);

} // namespace utils
} // namespace downloader