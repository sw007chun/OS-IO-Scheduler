/*
 * SSTF_IO_Scheduler.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: sungw
 */

#include "SSTF_IO_Scheduler.h"
#include <cstdlib>

SSTFScheduler::SSTFScheduler() {
	current_event = NULL;
}
void SSTFScheduler::addIORequest(IOEvent *new_IO_request) {
	io_q.push_back(new_IO_request);
}
IOEvent* SSTFScheduler::getIOEvent() {
	if (!io_q.empty()) {
		if (current_event == NULL)
			current_event = io_q.front();
		list <IOEvent*>::iterator it = io_q.begin();
		int current_position = current_event->GetTarget();
		int shortest_distance = abs(io_q.front()->GetTarget() - current_position);
//		cout << io_q.front()->GetOPNum() << endl;
		list <IOEvent*>::iterator shortest_event = it;
		it++;
		for (; it != io_q.end(); it++) {
			if (abs((*it)->GetTarget() - current_position) < shortest_distance) {
				shortest_distance = abs((*it)->GetTarget() - current_position);
				shortest_event = it;
			}
		}
		current_event = *shortest_event;
//		cout <<(*shortest_event)->GetOPNum() << endl;
		io_q.erase(shortest_event);
//		cout << io_q.front()->GetOPNum() << endl;
		return current_event;
	} else {
		return NULL;
	}
}



