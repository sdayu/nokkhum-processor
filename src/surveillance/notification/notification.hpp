/*
 * notification.hpp
 *
 *  Created on: Jan 22, 2013
 *      Author: superizer
 */

#ifndef NOKKHUM_NOTIFICATION_HPP_
#define NOKKHUM_NOTIFICATION_HPP_

#include <string>
#include "../processor/image_processor.hpp"

namespace nokkhum{

class Notification : public ImageProcessor {
private:
	int camera_id;
	std::string description;
public:
	Notification(ImageQueue &input_image_queue, int camera_id, std::string description);
	virtual ~Notification();
	void start();
	//void warn();
};

} /* namespace nokkhum */



#endif /* NOTIFICATION_HPP_ */
