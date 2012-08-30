//============================================================================
// Name        : main.cpp
// Author      : Thanathip Limna
// Version     :
// Copyright   :
// Description : Hello World in C++
//============================================================================
#include <iostream>
#include <string>
#include <glog/logging.h>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>

#include "surveillance/surveillance_manager.hpp"

int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "arg miss match" << std::endl;
		return -1;
	}

	const std::string default_log_directory = "/tmp/nokkhum-log/processor/";

	// process command args
	boost::program_options::options_description program_desc("Allowed options");
	program_desc.add_options()
        ("help", "produce help message")
        ("log_dir", boost::program_options::value<std::string>()->default_value(default_log_directory), "set logging directory")
        ("camera_id", boost::program_options::value<std::string>(), "set camera id")
        ;
    boost::program_options::positional_options_description pod;
    pod.add("camera_id", -1);

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(program_desc).positional(pod).run(), vm);
    boost::program_options::notify(vm);

    if (vm.count("help")) {
    	std::cout << program_desc << std::endl;
        return 1;
    }

    if (!vm.count("camera_id")) {
    	std::cerr << "required camera_id" << std::endl;
    	std::cout << program_desc << std::endl;
    	return 1;
    }

	std::string log_directory = vm["log_dir"].as<std::string>();
	if (*(log_directory.rbegin()) == '/'){
		log_directory = log_directory + vm["camera_id"].as<std::string>() + "/";
	}
	else	{
		log_directory = log_directory + "/" + vm["camera_id"].as<std::string>() + "/";
	}

	if (!boost::filesystem::exists(log_directory)) {

		if (boost::filesystem::create_directories(log_directory)) {
			// LOG(INFO) << "Create log dir name: " << p;
		}
	}

	// google log flags
	FLAGS_logbufsecs = 0;
	FLAGS_log_dir = log_directory.c_str();
	google::InitGoogleLogging(argv[0]);

	LOG(INFO) << "Surveillance constructor ... ";
	std::string attribute = vm["camera_id"].as<std::string>();
	nokkhum::SurveillanceManager sm(attribute);

	LOG(INFO) << "Wait for command ... ";
	sm.processCommand();
	LOG(INFO) << "End command ... ";

//	sm.stopSurveillanceApplication();
	LOG(INFO) << "End Surveillance ... ";

	return 0;
}
