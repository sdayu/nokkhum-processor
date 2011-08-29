/*
 * surveillance.hpp
 *
 *  Created on: Aug 26, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_SURVEILLANCE_HPP_
#define NOKKHUM_SURVEILLANCE_HPP_

#include <cppunit/TestFixture.h>

namespace nokkhum {

class Surveillance : public CppUnit::TestFixture{
public:
	Surveillance();
	virtual ~Surveillance();

	void testSurveillance();
};

} /* namespace nokkhum */
#endif /* NOKKHUM_SURVEILLANCE_HPP_ */
