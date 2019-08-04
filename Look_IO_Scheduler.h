/*
 * Look_IO_Scheduler.h
 *
 *  Created on: Aug 1, 2019
 *      Author: sungw
 */

#ifndef LOOK_IO_SCHEDULER_H_
#define LOOK_IO_SCHEDULER_H_

#include "IO_Scheduler.h"
#include <list>

class LookScheduler : public IOScheduler {
private:
	list <IOEvent*> io_q;
	IOEvent *current_event;
	int updown; //up = 1, down = -1
public:
	LookScheduler();
	~LookScheduler() { };
	void addIORequest(IOEvent *new_IO_request);
	IOEvent* getIOEvent(int current_track);
};

#endif /* LOOK_IO_SCHEDULER_H_ */
