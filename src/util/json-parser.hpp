/*
 * json-parser.hpp
 *
 *  Created on: Jul 5, 2011
 *      Author: boatkrap
 */

#ifndef JSON_PARSER_HPP_
#define JSON_PARSER_HPP_

namespace nokkhum {

class JsonParser {
public:
	JsonParser();
	virtual ~JsonParser();
	void parse();
};

} /* namespace nokkhum */
#endif /* JSON_PARSER_HPP_ */
