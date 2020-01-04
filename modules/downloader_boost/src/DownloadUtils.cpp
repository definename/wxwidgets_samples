#include "pch.h"

namespace downloader
{
namespace utils
{

std::string ParseInstallerLink(std::shared_ptr<std::stringstream> stream)
{
	ptree::ptree pt;
	ptree::ini_parser::read_ini(*stream, pt);

	return pt.get<std::string>("agent_installer_link");
}


} // namespace utils
} // namespace downloader