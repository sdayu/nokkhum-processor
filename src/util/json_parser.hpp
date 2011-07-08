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
	void parse_camera(json_spirit::Value value);

private:
	const json_spirit::mValue& find_value( const json_spirit::mObject& obj, const std::string& name  );

	std::map<std::string, std::string> camera_schema;
};

} /* namespace nokkhum */
#endif /* JSON_PARSER_HPP_ */
