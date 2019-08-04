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
IOEvent* LookScheduler::getIOEvent(int current_track) {
	if (!io_q.empty()) {
		int distance;
		int shortest_distance = -1;
		list <IOEvent*>::iterator it;
		list <IOEvent*>::iterator shortest_event;
		if (qtrace)
			cout << "\tGet: (";
		for (it = io_q.begin(); it != io_q.end(); it++) {
			//only target tracks in the same direction from the current position will have positive distance
			distance = updown * ((*it)->GetTarget() - current_track);
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
			if (qtrace && distance >= 0)
				cout << (*it)->GetOPNum() << ':' << abs((*it)->GetTarget() - current_track) << ' ';
		}
		//if there is no target to the same direction, shortest_distance will have negative value
		if (shortest_distance < 0) {
			updown = -1 * updown;	//change the direction
			if (qtrace)
				cout << ") --> change direction to " << updown << endl;
			getIOEvent(current_track);	//get the IO event again
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
