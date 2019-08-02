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
	bool end;
public:
	CLookScheduler();
	~CLookScheduler() { };
	void addIORequest(IOEvent *new_IO_request);
	IOEvent* getIOEvent();
};



#endif /* CLook_IO_SCHEDULER_H_ */
