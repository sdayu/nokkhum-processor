/*
 * face_recognition_attribute.cpp
 *
 *  Created on: Jul 21, 2011
 *      Author: boatkrap
 */

#include "face_recognition_attribute.hpp"

namespace nokkhum {

FaceRecognitionAttribute::FaceRecognitionAttribute(std::string name, std::string face_database, int interval) :
		ImageProcessorAttribute(name),face_database(face_database), interval(interval) {

}

FaceRecognitionAttribute::~FaceRecognitionAttribute() {
	// TODO Auto-generated destructor stub
}

int FaceRecognitionAttribute::getInterval() const {
	return interval;
}

void FaceRecognitionAttribute::setInterval(int interval) {
	this->interval = interval;
}

std::string FaceRecognitionAttribute::getFaceDatabase() const
{
       return face_database;
}

void FaceRecognitionAttribute::setFaceDatabase(std::string face_database)
{
        this->face_database = face_database;
}

} /* namespace nokkhum */
