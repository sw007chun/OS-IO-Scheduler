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
	is_empty = true;
}
void FLookScheduler::addIORequest(IOEvent *new_IO_request) {
	add_q->push_back(new_IO_request);
	is_empty = false;

	if (qtrace) {
		list <IOEvent*>::iterator it;
		cout << "   Q=" << !current_q_num << " ( ";
		for (it = add_q->begin(); it != add_q->end(); it++) {
			cout << (*it)->GetOPNum() << ':' << (*it)->GetTarget() << ' ' ;
	 	}
		cout << ')' << endl;
	}
}
IOEvent* FLookScheduler::getIOEvent(int current_track) {
	//swap active queue with add queue, if both queues are not empty
	if (active_q->empty() && !is_empty) {
		if (add_q->empty())
			is_empty = true;
		list <IOEvent*> *temp = add_q;
		add_q = active_q;
		active_q = temp;
		current_q_num = !current_q_num;
	}
	if (!active_q->empty() || !add_q->empty()) {
		if (!change_direction && qtrace) {
			cout << "AQ=" << current_q_num << " dir=" << updown << " curtrack=" << current_track << ":  ";
			list <IOEvent*>::iterator it;
			list <IOEvent*> *print_q;
			for (int i = 0; i < 2; i++) {
				if (current_q_num == i)
					print_q = active_q;
				else
					print_q = add_q;
				cout << "Q[" << i << "] = ( ";
				for (it = print_q->begin(); it != print_q->end(); it++) {
					cout << (*it)->GetOPNum() << ':' << (*it)->GetTarget() << ':' <<(*it)->GetTarget() - current_track << ' ';
				}
				cout << ")  ";
			}
			cout << endl;
		}

		int distance;
		int shortest_distance = -1;
		list <IOEvent*>::iterator it;
		list <IOEvent*>::iterator shortest_event;
		if (qtrace)
			cout << "\tGet: (";
		for (it = active_q->begin(); it != active_q->end(); it++) {
			distance = updown * ((*it)->GetTarget() - current_track);
			if (shortest_distance < 0 || (distance >= 0 && distance < shortest_distance)) {
				shortest_distance = distance;
				shortest_event = it;
			}
			if (qtrace && distance >= 0)
				cout << (*it)->GetOPNum() << ':' << (*it)->GetTarget() << ':' << abs((*it)->GetTarget() - current_track) << ' ';
		}
		if (shortest_distance < 0) {
			updown = -1 * updown;
			change_direction = true;
			if (qtrace)
				cout << ") --> change direction to " << updown << endl;
			getIOEvent(current_track);
			change_direction = false;
		} else {
			if (qtrace)
				cout << ") --> "<< (*shortest_event)->GetOPNum() <<" dir=" << updown << endl;
			current_event = *shortest_event;
			active_q->erase(shortest_event);
		}
	} else {
		current_event = NULL;
	}
	return current_event;
}
