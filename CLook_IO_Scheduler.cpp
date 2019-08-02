/*
 * CCLook_IO_Scheduler.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: sungw
 */

#include "CLook_IO_Scheduler.h"

CLookScheduler::CLookScheduler() {
	current_event = NULL;
	end = 1;
}
void CLookScheduler::addIORequest(IOEvent *new_IO_request) {
	io_q.push_back(new_IO_request);
}
IOEvent* CLookScheduler::getIOEvent() {
	if (!io_q.empty()) {
		if (current_event == NULL)
			current_event = io_q.front();
		list <IOEvent*>::iterator it = io_q.begin();
		int distance =  io_q.front()->GetTarget() - end * current_event->GetTarget();
		int shortest_distance = distance;
		list <IOEvent*>::iterator shortest_event = it;
		it++;
		for (; it != io_q.end(); it++) {
			distance =  ((*it)->GetTarget() - end * current_event->GetTarget());
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
		}
		end = 1;
		if (shortest_distance < 0) {
			end = 0;
			getIOEvent();
		} else {
			current_event = *shortest_event;
	//		cout <<(*shortest_event)->GetOPNum() << endl;
			io_q.erase(shortest_event);
	//		cout << io_q.front()->GetOPNum() << endl;
		}
		return current_event;
	} else {
		return NULL;
	}
}



