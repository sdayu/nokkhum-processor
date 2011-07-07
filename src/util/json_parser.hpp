/*
 * json-parser.hpp
 *
 *  Created on: Jul 5, 2011
 *      Author: boatkrap
 */

#ifndef JSON_PARSER_HPP_
#define JSON_PARSER_HPP_

#include <string>
#include <json_spirit.h>

namespace nokkhum {

class JsonParser {
public:
	JsonParser();
	virtual ~JsonParser();
	void parse(std::string file_name);
	void parseValue(json_spirit::Value, std::string type);

	std::map<std::string, std::string> camera_schema;
};

} /* namespace nokkhum */
#endif /* JSON_PARSER_HPP_ */
