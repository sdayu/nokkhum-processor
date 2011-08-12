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


namespace nokkhum {

ImageProcessorFactory::ImageProcessorFactory() {
	// TODO Auto-generated constructor stub

}

ImageProcessorFactory::~ImageProcessorFactory() {
	// TODO Auto-generated destructor stub
}

ImageProcessor *ImageProcessorFactory::getImageProcessor(
		ImageProcessorProperty *ipp) {
	if (ipp->getName() == "Motion Detector") {
		MotionDetectorProperty *mdp = dynamic_cast<MotionDetectorProperty*> (ipp);

	} else if (ipp->getName() == "Face Detector") {
		FaceDetectorProperty *fdp = dynamic_cast<FaceDetectorProperty*> (ipp);

	} else if (ipp->getName() == "Video Recorder") {
		VideoRecorderProperty *vrp = dynamic_cast<VideoRecorderProperty*> (ipp);

	} else if (ipp->getName() == "Image Recorder") {
		ImageRecorderProperty *irp = dynamic_cast<ImageRecorderProperty*> (ipp);

	}

	return nullptr;
}

} /* namespace nokkhum */
