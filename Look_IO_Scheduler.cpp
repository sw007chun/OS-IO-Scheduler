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
		int current_position = current_event == NULL ? 0 : current_event->GetTarget();
		int distance = updown * (io_q.front()->GetTarget() - current_position);
		int shortest_distance = INT_MIN;
		list <IOEvent*>::iterator it;
		list <IOEvent*>::iterator shortest_event;
		if (qtrace)
				cout << "\tGet: (";
		for (it = io_q.begin(); it != io_q.end(); it++) {
			distance = updown * ((*it)->GetTarget() - current_position);
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
			if (qtrace && distance >= 0)
				cout << (*it)->GetOPNum() << ':' << abs((*it)->GetTarget() - current_position) << ' ';
		}
		if (shortest_distance < 0) {
			updown = -1 * updown;
			if (qtrace)
				cout << ") --> change direction to " << updown << endl;
			getIOEvent();
		} else {
			if (qtrace)
				cout << ") --> "<< (*shortest_event)->GetOPNum() <<" dir=" << updown << endl;
			current_event = *shortest_event;
			io_q.erase(shortest_event);
		}
		return current_event;
	} else {
		return NULL;
	}
}
