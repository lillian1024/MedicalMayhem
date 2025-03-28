//
// Created by perra on 1/31/2025.
//

#include "doctorUtil.h"
#include "../cmdUtil/cmdUtil.h"
#include "../llistUtil/llist.h"

char*** weekSchedule = NULL;

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

int doctorhasName(doctor* doctor, char* name)
{
    return strcmp(doctor->name, name) == 0;
}

doctor* GetDoctorById(int id)
{
    int index = LL_IndexOf(DoctorList, (int(*)(void*, void*))&doctorHasId, &id);

    if (index < 0)
    {
        return NULL;
    }

    return (doctor*)LL_Get(DoctorList, index);
}

doctor* GetDoctorByName(char* name)
{
    int index = LL_IndexOf(DoctorList, (int(*)(void*, void*))&doctorhasName, name);

    if (index < 0)
    {
        return NULL;
    }

    return (doctor*)LL_Get(DoctorList, index);
}

doctor* GetDoctorBy()
{
    printf("Get doctor by: (1) id, (2) name\n");
    int choice = AskIntChoice(1, 2);

    doctor* doctor;

    if (choice == 1)
    {
        int id;

        printf("Please input the id of the doctor: ");
        scanf("%d", &id);

        doctor = GetDoctorById(id);
    }
    else
    {
        char doctorName[MAX_NAME_LEN+1];

        printf("Please input the name of the doctor: ");
        AskStr(doctorName, 3, MAX_NAME_LEN);

        doctor = GetDoctorByName(doctorName);
    }

    if (doctor == NULL)
    {
        printf("%sDoctor not found!%s\n", TTYRED, TTYDEF);
    }

    return NULL;
}

void assignDoctor(char ***schedule)
{
    int day, shift;
    char name[MAX_NAME_LEN];

    printf("Enter day (0=Monday, 6=Sunday): ");
    day = AskIntChoice(0, 6);

    printf("Enter shift (0=Morning, 1=Afternoon, 2=Evening): ");
    shift = AskIntChoice(0, 6);

    doctor* currentDoctor = GetDoctorBy();

    if (currentDoctor == NULL) 
    {
        return;
    }

    schedule[day][shift] = malloc(MAX_NAME_LEN);
    if (!schedule[day][shift]) {
        err(1, "Memory allocation failed for schedule slot");
    }
    strncpy(schedule[day][shift], name, MAX_NAME_LEN - 1);
    schedule[day][shift][MAX_NAME_LEN - 1] = '\0';

    printf("Doctor assigned successfully!\n");
}