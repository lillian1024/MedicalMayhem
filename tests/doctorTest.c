#include <stdio.h>
#include "../src/utils/doctorUtil/doctorUtil.h"
#include "../src/utils/doctorUtil/doctorScheduleUtil.h"

int main()
{
    // Create a weekly schedule
    char ***schedule = createSchedule();

    // Add doctors
    printf("\nAdding doctors...\n");
    addDoctor(&doctorLL, "Smith", 2, 1, 3);
    addDoctor(&doctorLL, "Johnson", 1, 2, 2);
    addDoctor(&doctorLL, "Brown", 3, 2, 1);

    // Assign doctors to shifts
    // Cannot use scanf in test files
    /*printf("\nAssigning doctors...\n");
    assignDoctor(schedule, &list);
    assignDoctor(schedule, &list);
    assignDoctor(schedule, &list);*/

    // Display the schedule
    printf("\nDisplaying schedule...\n");
    displayWeekSchedule(schedule);

    // Free dynamically allocated memory
    for (int i = 0; i < DAYS; i++) {
        for (int j = 0; j < SHIFTS; j++) {
            free(schedule[i][j]);
        }
        free(schedule[i]);
    }
    free(schedule);

    // Free the doctor list
    freeDoctorList(&doctorLL);
    /*doctor *current = list.head;
    while (current != NULL) {
        doctor *temp = current;
        current = current->next;
        free(temp);
    }*/
}