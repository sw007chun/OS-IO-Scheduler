/*
 * IOEvent.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: sungw
 */

#include "IO_Event.h"
#include <iostream>
#include <iomanip>
using namespace std;

IOEvent::IOEvent(int op_num, int arrival, int track) {
	this->op_num = op_num;
	this->arrival = arrival;
	this->track = track;
	start_time = 0;
	end_time = 0;
}
void IOEvent::SetStartTime(int time) {
	start_time = time;
}
void IOEvent::SetEndTime(int time) {
	end_time = time;
}
bool IOEvent::HasArrived(int time) {
	return arrival == time;
}
int IOEvent::GetOPNum() {
	return op_num;
}
int IOEvent::GetTarget() {
	return track;
}
int IOEvent::GetIOTime() {
	return end_time-arrival;
}
void IOEvent::Print() {
	cout << setw(5) << op_num << ": " << setw(5) << arrival << ' ' << setw(5) << start_time << ' ' << setw(5) << end_time << endl;
}
int IOEvent::GetTurnAroundTime() {
	return end_time - arrival;
}
int IOEvent::GetWaitTime() {
	return start_time - arrival;
}
