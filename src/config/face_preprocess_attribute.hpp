/*
 * face_preprocess_attribute.hpp
 *
 *  Created on: Jan 16, 2014
 *      Author: superizer
 */

#ifndef NOKKHUM_FACE_PREPROCESS_ATTRIBUTE_HPP_
#define NOKKHUM_FACE_PREPROCESS_ATTRIBUTE_HPP_

#include "image_processor_attribute.hpp"

#include <string>

namespace nokkhum {

class FacePreprocessAttribute : public nokkhum::ImageProcessorAttribute
{
public:
    FacePreprocessAttribute(std::string name, std::string face_database, int face_id, int face_num, int interval);
    virtual ~FacePreprocessAttribute();
    std::string getFaceDatabase() const;
    void setFaceDatabase(std::string face_database);
    int getFaceId() const;
    void setFaceId(int face_id);
    int getFaceNum() const;
    void setFaceNum(int face_num);
    int getInterval() const;
    void setInterval(int interval);

private:
    std::string face_database;
    int face_id;
    int face_num;
    int interval;
};

} /* namespace nokkhum */
#endif /* NOKKHUM_FACE_PREPROCESS_ATTRIBUTE_HPP_ */
