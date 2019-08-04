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
#include <climits>
#include "IO_Event.h"
using namespace std;

extern int qtrace;

class IOScheduler {
public:
	virtual ~IOScheduler() { };
	virtual void addIORequest(IOEvent *new_IO_request) = 0;
	virtual IOEvent* getIOEvent(int current_track) = 0;

};

#endif /* IO_SCHEDULER_H_ */
