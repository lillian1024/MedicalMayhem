//
// Created by perra on 1/31/2025.
//

#ifndef DOCTORSCHEDULEUTIL_H
#define DOCTORSCHEDULEUTIL_H

#include "doctorUtil.h"

extern int** weekSchedule;

void displayWeekSchedule(int** schedule);
int** createSchedule();
void destorySchedule(int** schedule);
void destoryWeekSchedule();
void assignDoctor(int** schedule);

#endif //DOCTORSCHEDULEUTIL_H
