//
// Created by perra on 1/31/2025.
//

#include "doctorUtil.h"
#include "../cmdUtil/cmdUtil.h"
#include "../llistUtil/llist.h"

int** weekSchedule = NULL;

void displayWeekSchedule(int** schedule)
{
    printf("\nWeekly Doctor Schedule:\n");
    for (int i = 0; i < DAYS; i++) {
        printf("%s:\n", weekdays[i]);
        for (int j = 0; j < SHIFTS; j++) 
        {
            if (schedule[i][j] < 0)
            {
                printf("  %s: %s\n", shiftNames[j], "(Not assigned)");
            }
            else
            {
                int doctorIndex = LL_IndexOf(DoctorList, (int(*)(void*,void*))&doctorHasId, &(schedule[i][j]));

                doctor* currentDoctor = LL_Get(DoctorList, doctorIndex);

                printf("  %s: %s\n", shiftNames[j], currentDoctor->name);
            }
        }
    }
}

int** createSchedule()
{
    int** schedule = malloc(DAYS * sizeof(int*));
    if (!schedule) 
    {
        errx(1, "Failed to allocate memory for schedule");
    }

    for (int i = 0; i < DAYS; i++) 
    {
        schedule[i] = malloc(SHIFTS * sizeof(int));
        if (!schedule[i]) 
        {
            errx(1, "Failed to allocate memory for shifts");
        }

        for (int j = 0; j < SHIFTS; j++) 
        {
            schedule[i][j] = -1;
        }
    }
    return schedule;
}

void destoryWeekSchedule()
{
    for (int i = 0; i < DAYS; i++) 
    {
        free(weekSchedule[i]);
    }

    free(weekSchedule);
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

        flushSTDIN();

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

        getchar();

        return NULL;
    }
    
    return doctor;
}

void assignDoctor(int** schedule)
{
    int day, shift;

    printf("Enter day (0=Monday, 6=Sunday): ");
    day = AskIntChoice(0, 6);

    printf("Enter shift (0=Morning, 1=Afternoon, 2=Evening): ");
    shift = AskIntChoice(0, 6);

    doctor* currentDoctor = GetDoctorBy();

    if (currentDoctor == NULL) 
    {
        return;
    }
    
    schedule[day][shift] = currentDoctor->id;

    printf("Doctor assigned successfully!\n");
}