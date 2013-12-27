/*
 * directory_manager.hpp
 *
 *  Created on: Oct 25, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_DIRECTORY_MANAGER_HPP_
#define NOKKHUM_DIRECTORY_MANAGER_HPP_

#include <string>
#include <ctime>
#include <chrono>
#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace nokkhum {

class DirectoryManager {
public:
	DirectoryManager(std::string root_directory, std::string type);
	DirectoryManager(std::string root_directory, std::string type, boost::posix_time::ptime the_time);
	DirectoryManager(std::string root_directory, std::string type, std::chrono::time_point<std::chrono::system_clock> date);
	virtual ~DirectoryManager();

	bool checkAndCreate();
	std::string getDirectoryName();

private:
	std::string root_directory;
	std::string type;
	boost::filesystem::path directory_path;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_DIRECTORY_MANAGER_HPP_ */
