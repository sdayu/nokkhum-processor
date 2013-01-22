/*
 * command_parser.hpp
 *
 *  Created on: Oct 6, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_COMMAND_PARSER_HPP_
#define NOKKHUM_COMMAND_PARSER_HPP_

#include <string>
#include <iostream>
#include <map>
#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/writer.h>

namespace nokkhum {

class CommandParser {
public:
	CommandParser();
	virtual ~CommandParser();

	bool paseCommand(std::string json);
	std::string getCommand();
	std::string getCameraAttribute();
	int getCameraId();

private:
	Json::Value value;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_COMMAND_PARSER_HPP_ */
