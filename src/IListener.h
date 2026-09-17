/*
 *  IListener.h
 *
 *  Created on: 15 Sep 2026
 *      Author: mchlp
 */

#ifndef UI_ILISTENER_H_
#define UI_ILISTENER_H_

#include <string>
#include <glm/glm.hpp>

class IListener
{
public:
    virtual ~IListener() = 0;

	virtual void on();
};

inline IListener::~IListener() {}

#endif /* UI_ILISTENER_H_ */
