/*
 * Disk.h
 *
 *  Created on: Jul 31, 2019
 *      Author: sungw
 */

#ifndef DISK_H_
#define DISK_H_


class Disk {
private:
	bool active;
	int track;
	int target;
	int total_movement;
public:
	Disk();
	void SetTargetTrack(int target);
	int GetCurrentTrack();
	void MoveTrack();
	bool HasReachedTarget();
	bool IsActive();
	void StopTrack();
	int GetTotalMovement();
};


#endif /* DISK_H_ */
