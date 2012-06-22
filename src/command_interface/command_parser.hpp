/*
 * command_parser.hpp
 *
 *  Created on: Oct 6, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_COMMAND_PARSER_HPP_
#define NOKKHUM_COMMAND_PARSER_HPP_

#include <string>
#include <map>
#include <jsoncpp/json/reader.h>

namespace nokkhum {

class CommandParser {
public:
	CommandParser();
	virtual ~CommandParser();

	bool paseCommand(std::string json);
	std::string getCommand();
	std::string getCameraAttribute();

private:
	Json::Value value;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_COMMAND_PARSER_HPP_ */
