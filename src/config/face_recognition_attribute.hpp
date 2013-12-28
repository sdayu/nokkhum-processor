/*
 * face_recognition_attribute.hpp
 *
 *  Created on: Nov 11, 2013
 *      Author: superizer
 */

#ifndef NOKKHUM_FACE_RECOGNITION_ATTRIBUTE_HPP_
#define NOKKHUM_FACE_RECOGNITION_ATTRIBUTE_HPP_

#include "image_processor_attribute.hpp"

#include <string>

namespace nokkhum {

class FaceRecognitionAttribute : public nokkhum::ImageProcessorAttribute
{
public:
    FaceRecognitionAttribute(std::string name, std::string face_database, int interval);
    virtual ~FaceRecognitionAttribute();
    std::string getFaceDatabase() const;
    void setFaceDatabase(std::string face_database);
    int getInterval() const;
    void setInterval(int interval);

private:
    std::string face_database;
    int interval;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_FACE_RECOGNITION_ATTRIBUTE_HPP_ */
