#include <stdio.h>
#include "config.h"
#include "utils/patientUtil/patientUtil.h"
#include "doctorUtil.h"
#include "doctorScheduleUtil.h"

int main()
{
    // Initialize doctor list
    doctorList list;
    list.head = NULL;

    // Create a weekly schedule
    char ***schedule = createSchedule();

    // Add doctors
    printf("\nAdding doctors...\n");
    addDoctor(&list, "Smith", 2, 1, 3);
    addDoctor(&list, "Johnson", 1, 2, 2);
    addDoctor(&list, "Brown", 3, 2, 1);

    // Assign doctors to shifts
    printf("\nAssigning doctors...\n");
    assignDoctor(schedule, &list);
    assignDoctor(schedule, &list);
    assignDoctor(schedule, &list);

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
    doctor *current = list.head;
    while (current != NULL) {
        doctor *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
