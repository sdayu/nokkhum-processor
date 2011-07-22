/*
 * face_detector_property.hpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_FACE_DETECTOR_PROPERTY_HPP_
#define NOKKHUM_FACE_DETECTOR_PROPERTY_HPP_

#include "image_processor_property.hpp"

#include <string>

namespace nokkhum {

class FaceDetectorProperty : public nokkhum::ImageProcessorProperty
{
public:
    FaceDetectorProperty(std::string name, int interval);
    virtual ~FaceDetectorProperty();
    int getInterval() const;
    void setInterval(int interval);

private:
    int interval;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_FACE_DETECTOR_PROPERTY_HPP_ */
