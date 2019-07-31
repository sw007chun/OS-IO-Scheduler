/*
 * Disk.cpp
 *
 *  Created on: Jul 31, 2019
 *      Author: sungw
 */

#include "Disk.h"

Disk::Disk() {
	active = false;
	track = 0;
	target = 0;
	total_movement = 0;
}
void Disk::SetTargetTrack(int new_target) {
	active = true;
	target = new_target;
}
int Disk::GetCurrentTrack() {
	return track;
}
void Disk::MoveTrack() {
	if (track < target) {
		track++;
	} else if (track > target)  {
		track--;
	}
	total_movement++;
}
bool Disk::HasReachedTarget() {
	return (track == target);
}
bool Disk::IsActive() {
	return active;
}
void Disk::StopTrack() {
	active = false;
}
int Disk::GetTotalMovement() {
	return total_movement;
}
