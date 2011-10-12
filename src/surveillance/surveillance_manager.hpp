/*
 * surveillance_manager.hpp
 *
 *  Created on: Oct 11, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_SURVEILLANCE_MANAGER_HPP_
#define NOKKHUM_SURVEILLANCE_MANAGER_HPP_

#include <string>
#include "video_surveillance.hpp"

namespace nokkhum {

class SurveillanceManager {
public:
	SurveillanceManager(std::string config);
	virtual ~SurveillanceManager();

	void processCommand();
	void startSurveillanceApplication();
	void stopSurveillanceApplication();
private:
	nokkhum::VideoSurveillance* vs;
	nokkhum::Configuration* conf;

};

} /* namespace nokkhum */
#endif /* NOKKHUM_SURVEILLANCE_MANAGER_HPP_ */
