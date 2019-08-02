/*
 * FLook_IO_Scheduler.cpp
 *
 *  Created on: Aug 1, 2019
 *      Author: sungw
 */


#include "FLook_IO_Scheduler.h"

FLookScheduler::FLookScheduler() {
	active_q = new list <IOEvent*>();
	add_q = new list <IOEvent*>();
	current_event = NULL;
	updown = 1;
}
void FLookScheduler::addIORequest(IOEvent *new_IO_request) {
	add_q->push_back(new_IO_request);
}
IOEvent* FLookScheduler::getIOEvent() {
	if (active_q->empty()) {
		list <IOEvent*> *temp = add_q;
		add_q = active_q;
		active_q = temp;
	}

	if (!active_q->empty() || !add_q->empty()) {
		if (current_event == NULL)
			current_event = active_q->front();
		list <IOEvent*>::iterator it = active_q->begin();
//		int current_position = current_event->GetTarget();
		int distance = updown * (active_q->front()->GetTarget() - current_event->GetTarget());
		int shortest_distance = distance;
		list <IOEvent*>::iterator shortest_event = it;
		it++;
		for (; it != active_q->end(); it++) {
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
			active_q->erase(shortest_event);
	//		cout << active_q->front()->GetOPNum() << endl;
		}
		return current_event;
	} else {
		return NULL;
	}
}


