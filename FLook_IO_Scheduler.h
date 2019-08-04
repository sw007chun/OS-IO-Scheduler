/*
 * FLook_IO_Scheduler.h
 *
 *  Created on: Aug 1, 2019
 *      Author: sungw
 */

#ifndef FLOOK_IO_SCHEDULER_H_
#define FLOOK_IO_SCHEDULER_H_

#include "IO_Scheduler.h"
#include <list>

extern int ftrace;

class FLookScheduler : public IOScheduler {
private:
	list <IOEvent*> *active_q;
	list <IOEvent*> *add_q;
	bool current_q_num;
	IOEvent *current_event;
	int updown; // up = -1, down = 1
	bool change_direction;
public:
	FLookScheduler();
	~FLookScheduler() { };
	void addIORequest(IOEvent *new_IO_request);
	IOEvent* getIOEvent();
};



#endif /* FLOOK_IO_SCHEDULER_H_ */
