/*
 * report.cpp
 *
 *  Created on: Jan 25, 2013
 *      Author: boatkrap
 */

#include "program_reporter.hpp"

#include <iostream>

namespace nokkhum {

ProgramReporter::ProgramReporter() {
	// TODO Auto-generated constructor stub

}

ProgramReporter::~ProgramReporter() {
	// TODO Auto-generated destructor stub
}

void ProgramReporter::report(Json::Value value) {
	std::cout << writer.write(value) << std::flush;
}

} /* namespace nokkhum */
