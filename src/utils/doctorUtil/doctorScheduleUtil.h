//
// Created by perra on 1/31/2025.
//

#ifndef DOCTORSCHEDULEUTIL_H
#define DOCTORSCHEDULEUTIL_H

#include "doctorUtil.h"

extern char*** weekSchedule;

void displayWeekSchedule(char ***schedule);
char ***createSchedule();
void assignDoctor(char ***schedule);

#endif //DOCTORSCHEDULEUTIL_H
