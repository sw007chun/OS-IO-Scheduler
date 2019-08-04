/*
 * SSTF_IO_Scheduler.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: sungw
 */

#include "SSTF_IO_Scheduler.h"

SSTFScheduler::SSTFScheduler() {
	current_event = NULL;
}
void SSTFScheduler::addIORequest(IOEvent *new_IO_request) {
	io_q.push_back(new_IO_request);
}
IOEvent* SSTFScheduler::getIOEvent() {
	if (!io_q.empty()) {
		int current_position = current_event == NULL ? 0 : current_event->GetTarget();
		int shortest_distance = INT_MAX;
		list <IOEvent*>::iterator it;
		list <IOEvent*>::iterator shortest_event;
		if (qtrace)
				cout << "\t";
		for (it=io_q.begin(); it != io_q.end(); it++) {
			if (abs((*it)->GetTarget() - current_position) < shortest_distance) {
				shortest_distance = abs((*it)->GetTarget() - current_position);
				shortest_event = it;
			}
			if (qtrace)
				cout << (*it)->GetOPNum() << ':' << abs((*it)->GetTarget() - current_position) << ' ';
		}
		if (qtrace)
			cout << endl;
		current_event = *shortest_event;
		io_q.erase(shortest_event);
		return current_event;
	} else {
		return NULL;
	}
}



