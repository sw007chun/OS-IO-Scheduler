/*
 * IO_Event.h
 *
 *  Created on: Jul 30, 2019
 *      Author: sungw
 */

#ifndef IO_EVENT_H_
#define IO_EVENT_H_

class IOEvent {
private:
	int op_num;
	int arrival;
	int track;
	int start_time;
	int end_time;
public:
	IOEvent(int op_num, int arrival, int track);
	void SetStartTime(int time);
	void SetEndTime(int time);
	bool HasArrived(int time);
	int GetOPNum();
	int GetTarget();
	int GetIOTime();
	int GetTurnAroundTime();
	int GetWaitTime();
	void Print();
};


#endif /* IO_EVENT_H_ */
