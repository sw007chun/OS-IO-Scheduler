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
	current_q_num = 1;
	current_event = NULL;
	updown = 1;
	change_direction = false;
}
void FLookScheduler::addIORequest(IOEvent *new_IO_request) {
	add_q->push_back(new_IO_request);
	if (qtrace) {
		list <IOEvent*>::iterator it;
		cout << "   Q=" << !current_q_num << " ( ";
		for (it = add_q->begin(); it != add_q->end(); it++) {
			cout << (*it)->GetOPNum() << ':' << (*it)->GetTarget() << ' ' ;
	 	}
		cout << ')' << endl;
	}
}
IOEvent* FLookScheduler::getIOEvent() {
	if (!active_q->empty() || !add_q->empty()) {
		if (active_q->empty()) {
			list <IOEvent*> *temp = add_q;
			add_q = active_q;
			active_q = temp;
			current_q_num = !current_q_num;
		}
		if (!change_direction && qtrace) {
			int current_position = current_event == NULL ? 0 : current_event->GetTarget();
			cout << "AQ=" << current_q_num << " dir=" << updown << " curtrack=" << current_position << ":  ";
			list <IOEvent*>::iterator it;
			list <IOEvent*> *print_q;
			for (int i = 0; i < 2; i++) {
				if (current_q_num == i)
					print_q = active_q;
				else
					print_q = add_q;
				cout << "Q[" << i << "] = ( ";
				for (it = print_q->begin(); it != print_q->end(); it++) {
					cout << (*it)->GetOPNum() << ':' << (*it)->GetTarget() << ':' <<(*it)->GetTarget() - current_position << ' ';
				}
				cout << ")  ";
			}
			cout << endl;
		}
		int current_position = current_event == NULL ? 0 : current_event->GetTarget();
		int distance = updown * (active_q->front()->GetTarget() - current_position);
		int shortest_distance = INT_MIN;
		list <IOEvent*>::iterator it;
		list <IOEvent*>::iterator shortest_event;
		if (qtrace)
				cout << "\tGet: (";
		for (it = active_q->begin(); it != active_q->end(); it++) {
			distance = updown * ((*it)->GetTarget() - current_position);
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
			if (qtrace && distance >= 0)
				cout << (*it)->GetOPNum() << ':' << (*it)->GetTarget() << ':' << abs((*it)->GetTarget() - current_position) << ' ';
		}
		if (shortest_distance < 0) {
			updown = -1 * updown;
			change_direction = true;
			if (qtrace)
				cout << ") --> change direction to " << updown << endl;
			getIOEvent();
			change_direction = false;
		} else {
			if (qtrace)
				cout << ") --> "<< (*shortest_event)->GetOPNum() <<" dir=" << updown << endl;
			current_event = *shortest_event;
			active_q->erase(shortest_event);
		}
//		return current_event;
	} else {
		current_event = NULL;
//		return NULL;
	}
	return current_event;
}


