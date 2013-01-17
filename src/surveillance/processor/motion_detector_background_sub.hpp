#ifndef NOKKHUM_MOTION_DETECTION_BACKGROUNDSUBTRACTION_HPP_
#define NOKKHUM_MOTION_DETECTION_BACKGROUNDSUBTRACTION_HPP_

#include "motion_detector.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/tracking.hpp>

namespace nokkhum{
class BackgroundMotionDetector : public nokkhum::MotionDetector{
public:
	BackgroundMotionDetector(ImageQueue &input_image_queue);
	BackgroundMotionDetector(ImageQueue &input_image_queue, MotionDetectorAttribute &mdp);
	virtual ~BackgroundMotionDetector();
	//void start();
private:
	cv::Mat BackgroundSubtraction(cv::Mat background, cv::Mat current);
	bool detectMotion(cv::Mat background, cv::Mat current);
};

}
#endif /* NOKKHUM_MOTION_DETECTION_BACKGROUNDSUBTRACTION_HPP_ */
