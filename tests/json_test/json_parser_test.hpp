/*
 * JsonParserTest.cpp
 *
 *  Created on: Jul 7, 2011
 *      Author: boatkrap
 */

#ifndef JSON_PASER_TEST_H_
#define JSON_PASER_TEST_H_

#include <cppunit/TestFixture.h>

namespace nokkhum {

class JsonParserTest: public CppUnit::TestFixture {
public:
	JsonParserTest();
	virtual ~JsonParserTest();

	void testJsonParser();
};

} /* namespace nokkhum */

#endif
