//============================================================================
// Name        : nokkhum-test.cpp
// Author      : Thanathip Limna
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestResult.h>

#include "json_test/json_parser_test.hpp"
#include "processor_builder/processor_builder.hpp"

int main() {
	cout << "Hello World, Hello Nukkhum" << endl; // prints Hello World, Hello Nukkhum


//	CppUnit::TestCaller<nokkhum::JsonParserTest> test( "testJsonParser",
//	                                             &nokkhum::JsonParserTest::testJsonParser );

	CppUnit::TestCaller<nokkhum::ProcessorBuilderTest> test( "testProcessorBuilder",
		                                             &nokkhum::ProcessorBuilderTest::testProcessorBuilder );

	CppUnit::TestResult result;
	test.run( &result );
	return 0;
}
