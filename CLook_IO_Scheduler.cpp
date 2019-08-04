/*
 * CCLook_IO_Scheduler.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: sungw
 */

#include "CLook_IO_Scheduler.h"

CLookScheduler::CLookScheduler() {
	current_event = NULL;
	not_end = true;
}
void CLookScheduler::addIORequest(IOEvent *new_IO_request) {
	io_q.push_back(new_IO_request);
}
IOEvent* CLookScheduler::getIOEvent(int current_track) {
	if (!io_q.empty()) {
		int distance;
		int shortest_distance = -1;
		list <IOEvent*>::iterator it;
		list <IOEvent*>::iterator shortest_event;
		if (qtrace && not_end)
			cout << "\tGet: (";
		for (it = io_q.begin(); it != io_q.end(); it++) {
			//if the disk has reached the final IO request to that direction set the distance to the next target from track 0
			//not_end=0 when disk has reached the end of that direction, else not_end=1
			distance = (*it)->GetTarget() - not_end * current_track;
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
			if (qtrace && distance >= 0 && not_end)
				cout << (*it)->GetOPNum() << ':' << abs((*it)->GetTarget() - current_track) << ' ';
		}
		//if there is no target to the same direction, shortest_distance will have negative value
		if (shortest_distance < 0) {
			not_end = false;
			getIOEvent(current_track);
		} else {
			if (qtrace)
				cout << ") --> " << ((not_end) ? "" : "go to bottom and pick ") << (*shortest_event)->GetOPNum() << endl;;
			current_event = *shortest_event;
			io_q.erase(shortest_event);
			not_end = true;
		}
		return current_event;
	} else {
		return NULL;
	}
}



