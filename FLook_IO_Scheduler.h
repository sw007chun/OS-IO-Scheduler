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

class FLookScheduler : public IOScheduler {
private:
	list <IOEvent*> *active_q;
	list <IOEvent*> *add_q;
	IOEvent *current_event;
	int updown; // up = -1, down = 1
public:
	FLookScheduler();
	~FLookScheduler() { };
	void addIORequest(IOEvent *new_IO_request);
	IOEvent* getIOEvent();
};



#endif /* FLOOK_IO_SCHEDULER_H_ */
