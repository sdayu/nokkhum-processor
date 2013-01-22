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
	MotionDetectorAttribute(std::string name, std::string motion_analysis_method, double sensitive, int interval);
	MotionDetectorAttribute(std::string name, std::string motion_analysis_method, double sensitive, int interval, bool enable_area_of_interest, point p1, point p2);
	virtual ~MotionDetectorAttribute();
    int getInterval() const;
    int getSensitive() const;
    void setInterval(int interval);
    void setSensitive(double sensitive);
    point getStartPoint() const;
    point getEndPoint() const;
    std::string getMotionAnalysis() const;
    bool getEnableAreaOfInterest() const;

private:
    double sensitive;
    int interval;
    std::string motion_analysis_method;
    point p1, p2;
    bool enable_area_of_interest;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_MOTION_DETECTOR_ATTRIBUTE_HPP_ */
