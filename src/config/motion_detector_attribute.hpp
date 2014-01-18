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
#include <opencv2/core/core.hpp>

namespace nokkhum {

class MotionDetectorAttribute: public nokkhum::ImageProcessorAttribute {
public:
	MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
			double sensitive, int interval,
			int wait_motion_time);
	MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
			double sensitive, int interval,
			int wait_motion_time,
			bool enable_area_of_interest, point p1, point p2);
	MotionDetectorAttribute(std::string name, std::string motion_analysis_method,
				double sensitive, int interval,
				int wait_motion_time,
				bool enable_area_of_interest, std::vector< std::vector<cv::Point> > mul_point,
				std::vector<std::string> area_name);
	virtual ~MotionDetectorAttribute();
    int getInterval() const;
    int getSensitive() const;
    void setInterval(int interval);
    void setSensitive(double sensitive);
    point getStartPoint() const;
    point getEndPoint() const;
    std::string getMotionAnalysis() const;
    bool getEnableAreaOfInterest() const;
    int getWaitMotionTime() const;
    void setWaitMotionTime(int seconds);
    std::vector< std::vector<cv::Point> > getMulPoint() const;
    void setMulPoint(std::vector< std::vector<cv::Point> > mul_point);
    std::vector<std::string> getAreaName() const;
    void setAreaName(std::vector<std::string> area_name);

private:
    std::vector< std::vector<cv::Point> > mul_point;
    double sensitive;
    int interval;
    std::vector<std::string> area_name;
    std::string motion_analysis_method;
    point p1, p2;
    bool enable_area_of_interest;
    int wait_motion_time;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_MOTION_DETECTOR_ATTRIBUTE_HPP_ */
