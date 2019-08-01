/*
 * IO_Scheduler.h
 *
 *  Created on: Jul 30, 2019
 *      Author: sungw
 */

#ifndef IO_SCHEDULER_H_
#define IO_SCHEDULER_H_

#include <iostream>
#include <cstdlib>
#include "IO_Event.h"
using namespace std;

class IOScheduler {
private:

public:
	IOScheduler();
	virtual ~IOScheduler() { };
	virtual void addIORequest(IOEvent *new_IO_request) = 0;
	virtual IOEvent* getIOEvent() = 0;

};

#endif /* IO_SCHEDULER_H_ */
