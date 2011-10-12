/*
 * command_parser.cpp
 *
 *  Created on: Oct 6, 2011
 *      Author: boatkrap
 */

#include "command_parser.hpp"

namespace nokkhum {

CommandParser::CommandParser() {
	// TODO Auto-generated constructor stub

}

CommandParser::~CommandParser() {
	// TODO Auto-generated destructor stub
}

void CommandParser::paseCommand(std::string json) {

	json_spirit::read(json, value);

}

std::string CommandParser::getCommand() {
	json_spirit::mObject obj = value.get_obj();

	return obj["action"].get_str();
}



} /* namespace nokkhum */
