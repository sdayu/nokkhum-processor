/*
 * face_recognition_attribute.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: superizer
 */

#include "face_preprocess_attribute.hpp"

namespace nokkhum {

FacePreprocessAttribute::FacePreprocessAttribute(std::string name, std::string face_database, int face_id , int face_num, int interval) :
		ImageProcessorAttribute(name), face_database(face_database), face_id(face_id), face_num(face_num), interval(interval) {

}

FacePreprocessAttribute::~FacePreprocessAttribute() {
	// TODO Auto-generated destructor stub
}

int FacePreprocessAttribute::getInterval() const {
	return interval;
}

void FacePreprocessAttribute::setInterval(int interval) {
	this->interval = interval;
}

int FacePreprocessAttribute::getFaceId() const {
	return face_id;
}

void FacePreprocessAttribute::setFaceId(int face_id) {
	this->face_id = face_id;
}

int FacePreprocessAttribute::getFaceNum() const {
	return face_num;
}

void FacePreprocessAttribute::setFaceNum(int face_num) {
	this->face_num = face_num;
}

std::string FacePreprocessAttribute::getFaceDatabase() const
{
       return face_database;
}

void FacePreprocessAttribute::setFaceDatabase(std::string face_database)
{
        this->face_database = face_database;
}

} /* namespace nokkhum */
