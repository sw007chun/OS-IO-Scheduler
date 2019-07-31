/*
 * FIFO_IO_Scheduler.h
 *
 *  Created on: Jul 30, 2019
 *      Author: sungw
 */

#ifndef FIFO_IO_SCHEDULER_H_
#define FIFO_IO_SCHEDULER_H_

#include "IO_Scheduler.h"
#include <queue>

class FIFOScheduler : public IOScheduler {
private:
	queue <IOEvent*> io_q;
public:
	FIFOScheduler();
	~FIFOScheduler() { };
	void addIORequest(IOEvent *new_IO_request);
	IOEvent* getIOEvent();
};


#endif /* FIFO_IO_SCHEDULER_H_ */
