/*
 * face_detector_attribute.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_FACE_DETECTOR_ATTRIBUTE_HPP_
#define NOKKHUM_FACE_DETECTOR_ATTRIBUTE_HPP_

#include "image_processor_attribute.hpp"

#include <string>

namespace nokkhum {

class FaceDetectorAttribute : public nokkhum::ImageProcessorAttribute
{
public:
    FaceDetectorAttribute(std::string name, int interval);
    virtual ~FaceDetectorAttribute();
    int getInterval() const;
    void setInterval(int interval);

private:
    int interval;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_FACE_DETECTOR_ATTRIBUTE_HPP_ */
