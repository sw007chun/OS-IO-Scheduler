/*
 * SSTF_IO_Scheduler.h
 *
 *  Created on: Jul 31, 2019
 *      Author: sungw
 */

#ifndef SSTF_IO_SCHEDULER_H_
#define SSTF_IO_SCHEDULER_H_

#include "IO_Scheduler.h"
#include <list>

class SSTFScheduler : public IOScheduler {
private:
	list <IOEvent*> io_q;
	IOEvent *current_event;
public:
	SSTFScheduler();
	~SSTFScheduler() { };
	void addIORequest(IOEvent *new_IO_request);
	IOEvent* getIOEvent(int current_track);
};

#endif /* SSTF_IO_SCHEDULER_H_ */
