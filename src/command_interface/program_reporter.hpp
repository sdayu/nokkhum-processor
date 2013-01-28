/*
 * report.hpp
 *
 *  Created on: Jan 25, 2013
 *      Author: boatkrap
 */

#ifndef NOKKHUM_PROGRAM_REPORTER_HPP_
#define NOKKHUM_PROGRAM_REPORTER_HPP_

#include <string>

#include <jsoncpp/json/writer.h>

namespace nokkhum {

class ProgramReporter {
public:
	ProgramReporter();
	virtual ~ProgramReporter();

	void report(Json::Value value);

private:
	Json::FastWriter writer;


};

} /* namespace nokkhum */
#endif /* NOKKHUM_PROGRAM_REPORTER_HPP_ */
