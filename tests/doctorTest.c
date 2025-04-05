#include <stdio.h>
#include "../src/utils/doctorUtil/doctorUtil.h"
#include "../src/utils/doctorUtil/doctorScheduleUtil.h"

int main()
{
    // Create a weekly schedule
    int** schedule = createSchedule();

    InitializeDoctorList();

    // Add doctors
    printf("\nAdding doctors...\n");
    addDoctor("Smith", 2, 1, 3);
    addDoctor("Johnson", 1, 2, 2);
    addDoctor("Brown", 3, 2, 1);

    // Assign doctors to shifts
    // Cannot use scanf in test files
    /*printf("\nAssigning doctors...\n");
    assignDoctor(schedule, &list);
    assignDoctor(schedule, &list);
    assignDoctor(schedule, &list);*/

    // Display the schedule
    printf("\nDisplaying schedule...\n");
    displayWeekSchedule(schedule);

    // Free the doctor list
    DisposeDoctorList();

    destorySchedule(schedule);
}