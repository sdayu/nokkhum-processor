/*
 * image_processor_factory.cpp
 *
 *  Created on: Aug 12, 2011
 *      Author: boatkrap
 */

#include "image_processor_factory.hpp"

#include "../../config/motion_detector_property.hpp"
#include "../../config/face_detector_property.hpp"
#include "../../config/video_recorder_property.hpp"
#include "../../config/image_recorder_property.hpp"

#include "face_detector.hpp"
#include "motion_detector.hpp"
#include "image_processor.hpp"
#include "video_recorder.hpp"
#include "image_recorder.hpp"

#include <iostream>
#include <vector>

namespace nokkhum {

ImageProcessorFactory::ImageProcessorFactory() {
	// TODO Auto-generated constructor stub

}

ImageProcessorFactory::~ImageProcessorFactory() {
	// TODO Auto-generated destructor stub
}

ImageProcessor *ImageProcessorFactory::getImageProcessor(
		ImageProcessorProperty *ipp, CvMatQueue* cv_mat_queue) {
	if (ipp->getName() == "Motion Detector") {
		MotionDetectorProperty *mdp = dynamic_cast<MotionDetectorProperty*>(ipp);
		MotionDetector *md = new MotionDetector(*cv_mat_queue);
		return md;

	} else if (ipp->getName() == "Face Detector") {
		FaceDetectorProperty *fdp = dynamic_cast<FaceDetectorProperty*>(ipp);
		FaceDetector *fd = new FaceDetector(*cv_mat_queue);
		return fd;
	} else if (ipp->getName() == "Video Recorder") {
		VideoRecorderProperty *vrp = dynamic_cast<VideoRecorderProperty*>(ipp);
		VideoRecorder *vr = new VideoRecorder()
	} else if (ipp->getName() == "Image Recorder") {
		ImageRecorderProperty *irp = dynamic_cast<ImageRecorderProperty*>(ipp);
		ImageRecorder *ir = new ImageRecorder(*cv_mat_queue);
		return ir;
	}

	return nullptr;
}

void ImageProcessorFactory::getImageProcessorPool(ImageProcessorProperty *ipp,
		MultipleMatQueue &mmq) {
	ImageProcessorProperty *tmp = nullptr;

	std::cout
			<< "-------------------------- Start Image Processor Property ------------------------------------"
			<< std::endl;

	std::cout << "name: " << ipp->getName() << std::endl;
	std::vector<ImageProcessor*> image_processor_pool;

	CvMatQueue cv_mat_queue;
	if (ipp->getName() != "default") {
		image_processor_pool.push_back(
				this->getImageProcessor(ipp, &cv_mat_queue));
	}

	auto imageProcessorPropertyVector = ipp->getImageProcessorPropertyVector();

	this->getImageProcessorFromVector(image_processor_pool,
			imageProcessorPropertyVector);

	std::cout
			<< "-------------------------- End Image Processor Property --------------------------------------"
			<< std::endl;
	for (auto i = 0; i < image_processor_pool.size(); i++) {
		if (image_processor_pool[i])
			std::cout << "Vector, processor name: "
					<< image_processor_pool[i]->getName() << std::endl;
		else
			std::cout << "Vector, processor name: nullptr" << std::endl;
	}
	std::cout
			<< "-------------------------- --> Image Processor Property --------------------------------------"
			<< std::endl;

}

void ImageProcessorFactory::getImageProcessorFromVector(
		std::vector<ImageProcessor*> & image_processor_pool,
		std::vector<ImageProcessorProperty*> & ippv) {

	CvMatQueue cv_mat_queue;
	for (std::vector<ImageProcessorProperty*>::size_type i = 0; i < ippv.size();
			i++) {
		std::cout << "Build processor name: " << ippv[i]->getName()
				<< std::endl;
		image_processor_pool.push_back(
				this->getImageProcessor(ippv[i], &cv_mat_queue));

		int size = ippv[i]->getImageProcessorPropertyVector().size();

		std::cout << "size: " << size << std::endl;
		if (size > 0){
			auto imageProcessorPropertyVector = ippv[i]->getImageProcessorPropertyVector();
			this->getImageProcessorFromVector(image_processor_pool, imageProcessorPropertyVector);
		}

	}

}

} /* namespace nokkhum */
