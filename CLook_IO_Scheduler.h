/*
 * CCLook_IO_Scheduler.h
 *
 *  Created on: Aug 1, 2019
 *      Author: sungw
 */

#ifndef CLook_IO_SCHEDULER_H_
#define CLook_IO_SCHEDULER_H_

#include "IO_Scheduler.h"
#include <list>

class CLookScheduler : public IOScheduler {
private:
	list <IOEvent*> io_q;
	IOEvent *current_event;
	bool not_end;	//flag to check if disk has not reached end of that direction
public:
	CLookScheduler();
	~CLookScheduler() { };
	void addIORequest(IOEvent *new_IO_request);
	IOEvent* getIOEvent(int current_track);
};

#endif /* CLook_IO_SCHEDULER_H_ */
