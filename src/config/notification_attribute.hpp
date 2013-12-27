/*
 * notification_attribute.hpp
 *
 *  Created on: Jan 23, 2013
 *      Author: superizer
 */

#include "image_processor_attribute.hpp"
#include <string>

#ifndef NOTIFICATION_ATTRIBUTE_HPP_
#define NOTIFICATION_ATTRIBUTE_HPP_
namespace nokkhum {

class NotificationAttribute : public nokkhum::ImageProcessorAttribute
{
public:
    NotificationAttribute(std::string name, std::string type);
    virtual ~NotificationAttribute();
    std::string getType() const;
private:
    std::string type;
};

} /* namespace nokkhum */



#endif /* NOTIFICATION_ATTRIBUTE_HPP_ */
