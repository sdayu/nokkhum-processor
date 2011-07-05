/*
 * json-parser.cpp
 *
 *  Created on: Jul 5, 2011
 *      Author: boatkrap
 */

#include "json-parser.hpp"

#include <iostream>
#include <fstream>

#include <json_spirit.h>

namespace nokkhum {

JsonParser::JsonParser() {
	// TODO Auto-generated constructor stub

}

JsonParser::~JsonParser() {
	// TODO Auto-generated destructor stub
}

void JsonParser::parse() {
	const char* file_name( "json.txt" );
	std::ifstream ifs(file_name);

	json_spirit::Value value;
	std::cout<<"Read JSON string: "<<json_spirit::read(ifs, value)<<std::endl;

	std::cout<<"JSON string: "<<std::endl<<json_spirit::write(value, json_spirit::pretty_print | json_spirit::raw_utf8)<<std::endl;

	json_spirit::Object obj = value.get_obj();

	for( int i = 0; i < obj.size(); i++){
	    json_spirit::Pair pair = obj[i];
		json_spirit::Value val = pair.value_;
		std::cout<<"Key: "<<pair.name_<<std::endl;

		std::cout<<"Property: "<<std::endl;
	}
}

} /* namespace nokkhum */
