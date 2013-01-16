#include "motion_detector_background_sub.hpp"

#include <iostream>
#include <glog/logging.h>
#include <ctime>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace nokkhum{

BackgroundMotionDetector::BackgroundMotionDetector(ImageQueue &input_image_queue) :
	MotionDetector(input_image_queue) {
	// TODO Auto-generated constructor stub
	name = "Background Motion Detection";

}

BackgroundMotionDetector::BackgroundMotionDetector(ImageQueue &input_image_queue, MotionDetectorAttribute &mdp) :
	MotionDetector(input_image_queue, mdp) {
	//std::cout << "hello background subtraction constructor :)" << std::endl;
	this -> name = "Background Motion Detection";
}

BackgroundMotionDetector::~BackgroundMotionDetector(){

}

/*void BackgroundMotionDetector::start() {

	//cv::Mat prevgray, gray, flow, cflow, frame; optical flow

	cv::Mat backgroundImage, currentImage;


	boost::posix_time::ptime current_time, motion_time;

	int motion_count = 0;

	int image_count = 0;

	std::vector<nokkhum::Image> tmp_image;
	nokkhum::Image image;
	bool motion_sequence = false;

	while (running) {

		if(input_image_queue.empty()){
			std::this_thread::sleep_for( std::chrono::microseconds( 1000 ) );
			continue;
		}

		image = input_image_queue.pop();
		tmp_image.push_back(image);

		if(++image_count < this->interval){
			continue;
		}
		else{
			image_count=0; //reset image count
		}

		motion_count = 0;

		currentImage = image.get();
		backgroundImage = currentImage.clone();

		if (backgroundImage.data) {

			// Background Subtraction
			currentImage = image.get();

			motion_count = this->DetectMotion(backgroundImage, currentImage);


			if(motion_count > 10){
//				cv::circle(cflow, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
//				std::cerr << "motion count: " << motion_count <<" sq: "<<motion_sequence << std::endl;
				//cv::circle(frame, cv::Point(20, 20), 10, CV_RGB(255, 0, 0), -1);
//				LOG(INFO) << "Have motion: " << std::dec << tmp_image.size() ;
//				std::cout<<"temporary queue size: "<< std::dec << tmp_image.size()<<std::endl;

				if (!motion_sequence){
					tmp_image[0].setMotionStatus(nokkhum::MotionStatus::BeginMotion);
					motion_sequence = true;
//					std::cerr << "start motion: " << motion_sequence << std::endl;
				}

				for(unsigned long i = 0; i<tmp_image.size();++i){
					this->push_to_output_image_queue(tmp_image[i]);
				}
				tmp_image.clear();
//				std::cout<<"affter clear: "<<tmp_image.size()<<std::endl;
				motion_time = boost::posix_time::microsec_clock::local_time();
			}
			else{
				current_time = boost::posix_time::microsec_clock::local_time();
				boost::posix_time::time_duration td = current_time - motion_time;

				// LOG(INFO) << "motion diff time: " << td.total_seconds();
				if(td.total_seconds() >= this->drop_motion){
//					LOG(INFO) << "Drop frame : " << std::dec << tmp_image.size() << "time: "<< td.total_seconds();
//					std::cout<<"drop frame:"<<tmp_image.size()<<std::endl;
					if (motion_sequence){
						tmp_image[0].setMotionStatus(nokkhum::MotionStatus::EndMotion);
						motion_sequence = false;
						this->push_to_output_image_queue(tmp_image[0]);
						//std::cerr << "end motion: " << motion_sequence << std::endl;
					}
//					std::cerr << "drop image: " << tmp_image.size() << std::endl;
					tmp_image.clear();

				}
				else{
					for(unsigned long i = 0; i<tmp_image.size();++i){
						this->push_to_output_image_queue(tmp_image[i]);
					}
//					LOG(INFO) << "write with out motion: "<<tmp_image.size();
					tmp_image.clear();

				}
//				std::cout<<"motion time : "<<boost::posix_time::to_simple_string(motion_time)<<std::endl;
//				std::cout<<"current time: "<<boost::posix_time::to_simple_string(current_time)<<std::endl;
//				std::cout<<"diff time   : "<<td<<std::endl;
			}

//			cv::imshow("Motion Detection", cflow);
		}

//		if (cv::waitKey(30) >= 0)
//			break;

		//std::swap(prevgray, gray);
	}
}*/

int BackgroundMotionDetector::detectMotion(cv::Mat background, cv::Mat current){
    // Convert to black and white
    //cv::Mat background_bw, current_bw,
	cv::Mat diff, thresh;
	//::cout << "hello background subtraction :)" << std::endl;
    //cv::cvtColor(background, background_bw, CV_RGB2GRAY);
    //cv::cvtColor(current, current_bw, CV_RGB2GRAY);
    diff = cv::abs(current - background);
    cv::threshold(diff,thresh,50,255,CV_THRESH_BINARY);
    return cv::countNonZero(thresh);
}
}
