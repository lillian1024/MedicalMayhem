//
// Created by perra on 1/31/2025.
//

#include "doctorUtil.h"

void displayWeekSchedule(char ***schedule){
    printf("\nWeekly Doctor Schedule:\n");
    for (int i = 0; i < DAYS; i++) {
        printf("%s:\n", weekdays[i]);
        for (int j = 0; j < SHIFTS; j++) {
            printf("  %s: %s\n", shiftNames[j], (schedule[i][j] == NULL) ? "(Not assigned)" : schedule[i][j]);
        }
    }
}

char ***createSchedule() {
    char ***schedule = malloc(DAYS * sizeof(char **));
    if (!schedule) {
        err(1, "Failed to allocate memory for schedule");
    }

    for (int i = 0; i < DAYS; i++) {
        schedule[i] = malloc(SHIFTS * sizeof(char *));
        if (!schedule[i]) {
            err(1, "Failed to allocate memory for shifts");
        }
        for (int j = 0; j < SHIFTS; j++) {
            schedule[i][j] = NULL;
        }
    }
    return schedule;
}

void assignDoctor(char ***schedule, doctorList *list) {
    int day, shift;
    char name[MAX_NAME_LEN];

    printf("Enter day (0=Monday, 6=Sunday): ");
    if (scanf("%d", &day) != 1 || day < 0 || day >= DAYS) {
        errx(1, "Invalid day input");
    }

    printf("Enter shift (0=Morning, 1=Afternoon, 2=Evening): ");
    if (scanf("%d", &shift) != 1 || shift < 0 || shift >= SHIFTS) {
        errx(1, "Invalid shift input");
    }

    printf("Enter doctor's name: ");
    if (scanf("%s", name) != 1) {
        errx(1, "Invalid doctor name input");
    }

    doctor *cpDoctor = list->head;
    while (cpDoctor != NULL) {
        if (strcmp(cpDoctor->name, name) == 0) {
            cpDoctor->nbShift[shift]++;
            break;
        }
        cpDoctor = cpDoctor->next;
    }

    if (cpDoctor == NULL) {
        printf("Doctor '%s' doesn't exist! Creating doctor record.\n", name);
        addDoctor(list, name, (shift == 0), (shift == 1), (shift == 2));
        cpDoctor = list->head;
    }

    schedule[day][shift] = malloc(MAX_NAME_LEN);
    if (!schedule[day][shift]) {
        err(1, "Memory allocation failed for schedule slot");
    }
    strncpy(schedule[day][shift], name, MAX_NAME_LEN - 1);
    schedule[day][shift][MAX_NAME_LEN - 1] = '\0';

    printf("Doctor assigned successfully!\n");
}