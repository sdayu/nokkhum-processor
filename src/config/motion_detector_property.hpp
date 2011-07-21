/*
 * motion_detector_property.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_MOTION_DETECTOR_PROPERTY_HPP_
#define NOKKHUM_MOTION_DETECTOR_PROPERTY_HPP_

#include "image_processor_property.hpp"
#include <string>

namespace nokkhum {

class MotionDetectorProperty: public nokkhum::ImageProcessorProperty {
public:
	MotionDetectorProperty(std::string name, int resolution, int interval);
	virtual ~MotionDetectorProperty();
    int getInterval() const;
    int getResolution() const;
    void setInterval(int interval);
    void setResolution(int resolution);
private:
    int interval;
    int resolution;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_MOTION_DETECTOR_PROPERTY_HPP_ */
