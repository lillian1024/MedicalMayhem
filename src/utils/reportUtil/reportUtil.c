#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../doctorUtil/doctorScheduleUtil.h"
#include "../doctorUtil/doctorUtil.h"
#include "../patientUtil/patientUtil.h"

typedef struct
    {
        int number;
        int count;
    }RoomData;

//Computation

int CountShifts(int doctorId)
{
    int count = 0;

    for (int i = 0; i < DAYS; i++) 
    {
        for (int j = 0; j < SHIFTS; j++) 
        {
            if (weekSchedule[i][j] == doctorId)
            {
                count++;
            }
        }
    }

    return count;
}

int GetMostBusyDoctor()
{
    int doctorId = -1;
    int maxShifts = -1;

    for (unsigned int i = 0; i < DoctorList->length; i++)
    {
        doctor* doctor = LL_Get(DoctorList, i);

        int nbShifts = CountShifts(doctor->id);

        if (nbShifts > maxShifts)
        {
            doctorId = doctor->id;
            maxShifts = nbShifts;
        }
    }

    return doctorId;
}

int GetLeastBusyDoctor()
{
    int doctorId = -1;
    int maxShifts = -1;

    for (unsigned int i = 0; i < DoctorList->length; i++)
    {
        doctor* doctor = LL_Get(DoctorList, i);

        int nbShifts = CountShifts(doctor->id);

        if (nbShifts < maxShifts || doctorId <= -1)
        {
            doctorId = doctor->id;
            maxShifts = nbShifts;
        }
    }

    return doctorId;
}

double GetAverageNbShift()
{
    int most = GetMostBusyDoctor();
    int least = GetLeastBusyDoctor();

    double mostShifts = (double)CountShifts(most);
    double leastShifts = (double)CountShifts(least);

    return (mostShifts + leastShifts) / 2.0;
}

int GetNbShiftsCovered()
{
    int count = 0;

    for (int i = 0; i < DAYS; i++) 
    {
        for (int j = 0; j < SHIFTS; j++) 
        {
            if (weekSchedule[i][j] >= 0)
            {
                count++;
            }
        }
    }

    return count;
}

int GetTotalShifts()
{
    return DAYS * SHIFTS;
}

LL_Sentinel* GetRoomUsage()
{
    LL_Sentinel* list = LL_Create();

    LL_Sentinel* patientList = GetAllPatientsRecords();

    for (unsigned int i = 0; i < patientList->length; i++)
    {
        int found = 0;

        int roomNumber = ((Patient*)LL_Get(patientList, i))->RoomNumber;

        for (unsigned int j = 0; j < list->length; j++)
        {
            RoomData* room = ((RoomData*)LL_Get(list, j));
            if (room->number == roomNumber)
            {
                room->count++;

                found = 1;

                break;
            }
        }

        if (!found)
        {
            RoomData* room = malloc(sizeof(RoomData));

            room->number = roomNumber;
            room->count = 1;

            LL_Append(list, room);
        }
    }

    return list;
}

void DisposeRoom(void* room, void* nothing)
{
    (void)nothing;

    free(room);
}

void DisposeRoomUsage(LL_Sentinel* list)
{
    LL_ForEach(list, DisposeRoom, NULL);

    LL_Dispose(list);
}

void GetRoomStats(int* lowestUsage, int* highestUsage, double* averageUsage)
{
    LL_Sentinel* list = GetRoomUsage();

    int lowest = -1;

    for (unsigned int i = 0; i < list->length; i++)
    {
        RoomData* room = (RoomData*)LL_Get(list, i);

        if (room->count < lowest || lowest < 0)
        {
            lowest = room->count;
        }
    }

    int highest = -1;

    for (unsigned int i = 0; i < list->length; i++)
    {
        RoomData* room = (RoomData*)LL_Get(list, i);

        if (room->count > highest || highest < 0)
        {
            highest = room->count;
        }
    }

    *lowestUsage = lowest;
    *highestUsage = highest;

    *averageUsage = ((double)lowest + (double)highest) / 2.0;

    DisposeRoomUsage(list);
}

//Report formating

char* GetDoctorReport()
{
    int mostShifts = CountShifts(GetMostBusyDoctor());
    int leastShifts = CountShifts(GetLeastBusyDoctor());
    double averageShifts = GetAverageNbShift();

    int shiftsCovered = GetNbShiftsCovered();
    double shiftsCoverage = ((double)shiftsCovered)/((double)GetTotalShifts());

    char buffer[512];

    sprintf(buffer, "The number of shifts covered for this week is %d, which coresponds to a coverage of %.0f%% of all shifts.\nThe average number of shifts per doctor is %.1f.\nThe doctor with the most amount of shifts has %d shifts this week.\nThe doctor with the least amount of shifts has %d shifts this week.\n",
        shiftsCovered,
        shiftsCoverage * 100,
        averageShifts,
        mostShifts,
        leastShifts);

    char* result = calloc(strlen(buffer)+1, sizeof(char));

    strcpy(result, buffer);

    return result;
}

char* GetEquipmentReport()
{
    int highestUsage, lowestUsage;
    double averageUsage;

    GetRoomStats(&lowestUsage, &highestUsage, &averageUsage);

    char buffer[512];

    sprintf(buffer, "The average number of patients in a room is %.1f.\nThe least utilized room has %d patients.\nThe most utilized room has %d patients.\n",
        averageUsage,
        lowestUsage,
        highestUsage);

    char* result = calloc(strlen(buffer)+1, sizeof(char));

    strcpy(result, buffer);

    return result;
}
