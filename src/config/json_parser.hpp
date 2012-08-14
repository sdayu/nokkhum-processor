/*
 * json-parser.hpp
 *
 *  Created on: Jul 5, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_JSON_PARSER_HPP_
#define NOKKHUM_JSON_PARSER_HPP_

#include <string>
#include <map>
#include <memory>
#include <jsoncpp/json/reader.h>
#include "../surveillance/processor/image_processor.hpp"
#include "../camera/camera.hpp"
#include "image_processor_attribute.hpp"
#include "camera_attribute.hpp"

#include "attribute.hpp"

namespace nokkhum {

typedef std::map<std::string, std::shared_ptr<Attribute>> AttributeMap;

class JsonParser {
public:
	JsonParser();
	virtual ~JsonParser();

	std::shared_ptr<AttributeMap> parse(std::string file_name);

	std::shared_ptr<CameraAttribute> parseCamera(const Json::Value camera_obj);
	void parseImageProcessor(const Json::Value image_processor_array, std::shared_ptr<ImageProcessorAttribute> ipp);

private:

	std::shared_ptr<ImageProcessorAttribute> parseVideoRecorder(const Json::Value image_processor_obj);
	std::shared_ptr<ImageProcessorAttribute> parseImageRecorder(const Json::Value image_processor_obj);
	std::shared_ptr<ImageProcessorAttribute> parseMotionDetector(const Json::Value image_processor_obj);
	std::shared_ptr<ImageProcessorAttribute> parseFaceDetector(const Json::Value image_processor_obj);

};

} /* namespace nokkhum */
#endif /* NOKKHUM_JSON_PARSER_HPP_ */
