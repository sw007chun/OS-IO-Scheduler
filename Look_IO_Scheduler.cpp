/*
 * Look_IO_Scheduler.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: sungw
 */


#include "Look_IO_Scheduler.h"

LookScheduler::LookScheduler() {
	current_event = NULL;
	updown = 1;
}
void LookScheduler::addIORequest(IOEvent *new_IO_request) {
	io_q.push_back(new_IO_request);
}
IOEvent* LookScheduler::getIOEvent() {
	if (!io_q.empty()) {
		if (current_event == NULL)
			current_event = io_q.front();
		list <IOEvent*>::iterator it = io_q.begin();
//		int current_position = current_event->GetTarget();
		int distance = updown * (io_q.front()->GetTarget() - current_event->GetTarget());
		int shortest_distance = distance;
		list <IOEvent*>::iterator shortest_event = it;
		it++;
		for (; it != io_q.end(); it++) {
			distance = updown * ((*it)->GetTarget() - current_event->GetTarget());
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
		}
		if (shortest_distance < 0) {
			updown = -1 * updown;
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

