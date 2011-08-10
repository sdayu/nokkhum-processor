/*
 * JsonParserTest.cpp
 *
 *  Created on: Jul 7, 2011
 *      Author: boatkrap
 */

#ifndef PROCESSOR_BUILDER_TEST_H_
#define PROCESSOR_BUILDER_TEST_H_

#include <cppunit/TestFixture.h>

namespace nokkhum {

class ProcessorBuilderTest: public CppUnit::TestFixture {
public:
	ProcessorBuilderTest();
	virtual ~ProcessorBuilderTest();

	void testProcessorBuilder();
};

} /* namespace nokkhum */

#endif
