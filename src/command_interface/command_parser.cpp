/*
 * command_parser.cpp
 *
 *  Created on: Oct 6, 2011
 *      Author: boatkrap
 */

#include "command_parser.hpp"
#include <glog/logging.h>
namespace nokkhum {

CommandParser::CommandParser() {
	// TODO Auto-generated constructor stub

}

CommandParser::~CommandParser() {
	// TODO Auto-generated destructor stub
}

bool CommandParser::paseCommand(std::string json) {

	bool result = json_spirit::read(json, value);
	return result;

}

std::string CommandParser::getCommand() {
	json_spirit::mObject obj = value.get_obj();

	return obj["action"].get_str();
}

std::string CommandParser::getCameraAttribute() {
	json_spirit::mObject obj = value.get_obj();

	return obj["attributes"].get_str();
}

} /* namespace nokkhum */
