/*
 * image_processor_factory.cpp
 *
 *  Created on: Aug 12, 2011
 *      Author: boatkrap
 */

#include "image_processor_factory.hpp"

#include "../../config/motion_detector_attribute.hpp"
#include "../../config/face_detector_attribute.hpp"
#include "../../config/video_recorder_attribute.hpp"
#include "../../config/image_recorder_attribute.hpp"

#include "face_detector.hpp"
#include "motion_detector.hpp"
#include "image_processor.hpp"
#include "video_recorder.hpp"
#include "image_recorder.hpp"
#include "video_motion_recorder.hpp"

#include <iostream>
#include <vector>
#include <exception>

namespace nokkhum {

ImageProcessorFactory::ImageProcessorFactory() {
	// TODO Auto-generated constructor stub

}

ImageProcessorFactory::~ImageProcessorFactory() {
	// TODO Auto-generated destructor stub
}

ImageProcessor *ImageProcessorFactory::getImageProcessor(
		ImageProcessorAttribute *ipp, CvMatQueue* cv_mat_queue) {
	if (ipp->getName() == "Motion Detector") {
		MotionDetectorAttribute *mdp = dynamic_cast<MotionDetectorAttribute*>(ipp);
		MotionDetector *md = new MotionDetector(*cv_mat_queue, mdp);
		return md;

	} else if (ipp->getName() == "Face Detector") {
		FaceDetectorAttribute *fdp = dynamic_cast<FaceDetectorAttribute*>(ipp);
		FaceDetector *fd = new FaceDetector(*cv_mat_queue, fdp);
		return fd;

	} else if (ipp->getName() == "Video Recorder") {
		VideoRecorderAttribute *vrp = dynamic_cast<VideoRecorderAttribute*>(ipp);
		VideoRecorder *vr = new VideoRecorder(*cv_mat_queue, vrp);
		return vr;

	} else if (ipp->getName() == "Video Motion Recorder") {
		VideoRecorderAttribute *vrp = dynamic_cast<VideoRecorderAttribute*>(ipp);
		VideoMotionRecorder *vmr = new VideoMotionRecorder(*cv_mat_queue, vrp);
		return vmr;

	} else if (ipp->getName() == "Image Recorder") {
		ImageRecorderAttribute *irp = dynamic_cast<ImageRecorderAttribute*>(ipp);
		ImageRecorder *ir = new ImageRecorder(*cv_mat_queue, irp);
		return ir;
	}

	return nullptr;
}

std::vector<ImageProcessor*> ImageProcessorFactory::getImageProcessorPool(
		ImageProcessorAttribute *ipp, MultipleMatQueue &mmq) {
	ImageProcessor *tmp = nullptr;

//	std::cout
//			<< "-------------------------- Start Image Processor Attribute ------------------------------------"
//			<< std::endl;
//
//	std::cout << "name: " << ipp->getName() << std::endl;
//	std::cout << "mmq size: " << mmq.getSize() << std::endl;
	std::vector<ImageProcessor*> image_processor_pool;

	CvMatQueue cv_mat_queue;
	if (ipp->getName() != "default") {

	}

	auto ippv = ipp->getImageProcessorAttributeVector();

	for (std::vector<ImageProcessorAttribute*>::size_type i = 0; i < ippv.size();
			i++) {
//		std::cout << "Build processor name V1: " << ippv[i]->getName()
//				<< std::endl;

		CvMatQueue *cv_mat_queue = mmq.get(i);

//		std::cout << "get queue " << std::endl;

		tmp = this->getImageProcessor(ippv[i], cv_mat_queue);
		image_processor_pool.push_back(tmp);

		int size = ippv[i]->getImageProcessorAttributeVector().size();

//		std::cout << "size: " << size << std::endl;
		if (size > 0) {
			auto imageProcessorAttributeVector =
					ippv[i]->getImageProcessorAttributeVector();
			this->getImageProcessorFromVector(image_processor_pool,
					imageProcessorAttributeVector, tmp);
		}

	}

//	std::cout
//			<< "-------------------------- Show Image Processor Attribute --------------------------------------"
//			<< std::endl;
//	for (unsigned long i = 0; i < image_processor_pool.size(); i++) {
//		if (image_processor_pool[i])
//			std::cout << "Vector, processor name: "
//					<< image_processor_pool[i]->getName() << std::endl;
//		else
//			std::cout << "Vector, processor name: nullptr" << std::endl;
//	}
//	std::cout
//			<< "-------------------------- End Image Processor Attribute --------------------------------------"
//			<< std::endl;

	return image_processor_pool;

}

void ImageProcessorFactory::getImageProcessorFromVector(
		std::vector<ImageProcessor*> & image_processor_pool,
		std::vector<ImageProcessorAttribute*> & ippv,
		ImageProcessor *parent_image_processor) {

	ImageProcessor *tmp = nullptr;
	for (std::vector<ImageProcessorAttribute*>::size_type i = 0; i < ippv.size();
			i++) {
//		std::cout << "Build processor name recursive: " << ippv[i]->getName()
//				<< std::endl;

		CvMatQueue *cv_mat_queue =
				parent_image_processor->getNewOutputImageQueue();
		tmp = this->getImageProcessor(ippv[i], cv_mat_queue);
		image_processor_pool.push_back(tmp);

		int size = ippv[i]->getImageProcessorAttributeVector().size();

//		std::cout << "size: " << size << std::endl;
		if (size > 0) {
			auto imageProcessorAttributeVector =
					ippv[i]->getImageProcessorAttributeVector();
			this->getImageProcessorFromVector(image_processor_pool,
					imageProcessorAttributeVector, tmp);
		}

	}

}

} /* namespace nokkhum */
