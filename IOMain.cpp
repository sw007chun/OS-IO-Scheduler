/*
 * IOMain.cpp
 *
 *  Created on: Jul 30, 2019
 *      Author: sungw
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <unistd.h>
#include "Disk.h"
#include "IO_Scheduler.h"
#include "FIFO_IO_Scheduler.h"
#include "SSTF_IO_Scheduler.h"
#include "Look_IO_Scheduler.h"
#include "CLook_IO_Scheduler.h"
#include "FLook_IO_Scheduler.h"
#include "IO_Event.h"
using namespace std;

int dotrace = 0;
int qtrace = 0;
int ftrace = 0;

#define trace(fmt...) do { if (dotrace > 0) { cout << fmt << endl; fflush(stdout); } } while (0)

int main (int argc, char* argv[]) {
	char c, algo;
 	ifstream input_file;
	IOScheduler *sched;

	while ((c= getopt(argc, argv, "s:qvf")) != -1) {
		switch (c) {
		case 's':
			algo = *optarg;
			break;
		case 'q':
			qtrace = 1;
			break;
		case 'v':
			dotrace = 1;
			break;
		case 'f':
			ftrace = 1;
			break;
		case '?':
			break;
		default:
			break;
		}
	}

	switch (algo) {
	case 'i':
		sched = new FIFOScheduler();
		break;
	case 'j':
		sched = new SSTFScheduler();
		break;
	case 's':
		sched = new LookScheduler();
		break;
	case 'c':
		sched = new CLookScheduler();
		break;
	case 'f':
		sched = new FLookScheduler();
		break;
	case '?':
		break;
	default:
		break;
	}

	input_file.open(argv[optind]);
	if (!input_file.is_open()) {
		cout << "Not a valid input file: " << argv[optind] << endl;
		return  1;
	}
	vector <IOEvent *> io_arrival;
	string readline;
	getline(input_file, readline);
	getline(input_file, readline);
	IOEvent *new_io;
	int op_num = 0;
	int arrival;
	int track;

	while (input_file >> arrival >> track) {
		new_io = new IOEvent(op_num, arrival, track);
		io_arrival.push_back(new_io);
		op_num++;
	}
	input_file.close();

	int current_time = 0;
	int current_io_num = 0;
	Disk disk;
	IOEvent *current_io = NULL;
	trace("TRACE");
	while (true) {
		if (current_io_num < op_num && io_arrival.at(current_io_num)->HasArrived(current_time)) {
			trace( left << current_time << ": " << right << setw(5) << current_io_num << " add " << io_arrival.at(current_io_num)->GetTarget() );
			sched->addIORequest(io_arrival.at(current_io_num));
			current_io_num++;
		}
		if (disk.IsActive()){
			if (disk.HasReachedTarget()) {
				if (current_time == 1271)
					cout << ' ' <<endl;
				current_io->SetEndTime(current_time);
				trace( left << current_time << ": " << right << setw(5) << current_io->GetOPNum() << " finish " << current_io->GetIOTime() );
				disk.StopTrack();
			}
			if (!disk.HasReachedTarget()) {
				disk.MoveTrack();
				current_time++;
			}
		}
		if (!disk.IsActive()) {
			current_io = sched->getIOEvent();
			if (current_io != NULL) {
				disk.SetTargetTrack(current_io->GetTarget());
				current_io->SetStartTime(current_time);
				trace( left << current_time << ": " << right << setw(5) << current_io->GetOPNum() << " issue " << current_io->GetTarget() << ' ' << disk.GetCurrentTrack() );
			} else if (current_io_num == op_num){
				break;
			} else {
				current_time++;
			}
		}
	}

	double avg_turnaround = 0;
	double avg_waittime = 0;
	int max_waittime = 0;

	for (int i = 0; i < op_num; i++) {
		io_arrival.at(i)->Print();
		avg_turnaround += io_arrival.at(i)->GetTurnAroundTime();
		avg_waittime += io_arrival.at(i)->GetWaitTime();
		if (io_arrival.at(i)->GetWaitTime() > max_waittime)
			max_waittime = io_arrival.at(i)->GetWaitTime();
	}
	avg_waittime /= op_num;
	avg_turnaround /= op_num;
	cout << fixed << "SUM: " <<  current_time << ' ' << disk.GetTotalMovement() << ' ' << setprecision(2) << setfill('0') << avg_turnaround << ' ' << setprecision(2) << setfill('0') << avg_waittime << ' ' << max_waittime << endl;
}
