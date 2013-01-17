/*
 * Attribute.h
 *
 *  Created on: Jul 22, 2011
 *      Author: boatkrap
 */

#ifndef NOKKHUM_ATTRIBUTE_HPP_
#define NOKKHUM_ATTRIBUTE_HPP_

namespace nokkhum {

class Attribute {
public:
	Attribute();
	virtual ~Attribute();
};

typedef struct p{
	int x;
	int y;
} point;


} /* namespace nokkhum */
#endif /* NOKKHUM_ATTRIBUTE_HPP_ */
