/*
 * motion_detector_attribute.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_MOTION_DETECTOR_ATTRIBUTE_HPP_
#define NOKKHUM_MOTION_DETECTOR_ATTRIBUTE_HPP_

#include "image_processor_attribute.hpp"
#include <string>

namespace nokkhum {

class MotionDetectorAttribute: public nokkhum::ImageProcessorAttribute {
public:
	MotionDetectorAttribute(std::string name, std::string motion_analysis_method, int resolution, int interval);
	virtual ~MotionDetectorAttribute();
    int getInterval() const;
    int getResolution() const;
    void setInterval(int interval);
    void setResolution(int resolution);
    std::string getMotionAnalysis() const;

private:
    int resolution;
    int interval;
    std::string motion_analysis_method;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_MOTION_DETECTOR_ATTRIBUTE_HPP_ */
