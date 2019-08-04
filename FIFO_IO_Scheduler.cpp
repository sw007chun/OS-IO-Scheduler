/*
 * FIFO_IO_Scheduler.cpp
 *
 *  Created on: Jul 30, 2019
 *      Author: sungw
 */

#include "FIFO_IO_Scheduler.h"

void FIFOScheduler::addIORequest(IOEvent *new_IO_request) {
	io_q.push(new_IO_request);
}
IOEvent* FIFOScheduler::getIOEvent(int current_track) {
	if (!io_q.empty()) {
		IOEvent *temp = io_q.front();
		io_q.pop();
		return temp;
	} else {
		return NULL;
	}
}
