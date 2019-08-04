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
		int current_position = current_event == NULL ? 0 : current_event->GetTarget();
		int distance = io_q.front()->GetTarget() - end * current_position;
		int shortest_distance = INT_MIN;
		list <IOEvent*>::iterator it;
		list <IOEvent*>::iterator shortest_event;
		if (qtrace && end)
				cout << "\tGet: (";
		for (it = io_q.begin(); it != io_q.end(); it++) {
			distance = (*it)->GetTarget() - end * current_position;
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
			if (qtrace && distance >= 0 && end)
				cout << (*it)->GetOPNum() << ':' << abs((*it)->GetTarget() - current_position) << ' ';
		}
//		end = 1;
		if (shortest_distance < 0) {
			end = 0;
			getIOEvent();
		} else {
			if (qtrace)
				cout << ") --> " << ((end) ? "" : "go to bottom and pick ") << (*shortest_event)->GetOPNum() << endl;;
			current_event = *shortest_event;
			io_q.erase(shortest_event);
			end = 1;
		}
		return current_event;
	} else {
		return NULL;
	}
}



