#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "reportUtil.h"
#include "../doctorUtil/doctorScheduleUtil.h"
#include "../doctorUtil/doctorUtil.h"
#include "../patientUtil/patientUtil.h"

typedef struct
    {
        int number;
        int count;
    }RoomData;

#define  BUFFER_DOCTOR_SIZE  100
#define  OBSERVATION_BUFFER  200
#define  PATIENT_BUFFER      512

char *diseases[] = {
    "Common Cold",
    "Influenza (Flu)",
    "COVID-19",
    "Pneumonia",
    "Tuberculosis (TB)",
    "Malaria",
    "Hepatitis (A, B, C, D, E)",
    "Dengue Fever",
    "HIV/AIDS",
    "Chickenpox",
    "Diabetes (Type 1 & Type 2)",
    "Hypertension (High Blood Pressure)",
    "Heart Disease",
    "Stroke",
    "Asthma",
    "Chronic Obstructive Pulmonary Disease (COPD)",
    "Arthritis",
    "Kidney Disease",
    "Alzheimer’s Disease",
    "Parkinson’s Disease",
    "Epilepsy",
    "Depression",
    "Anxiety Disorders",
    "Lung Cancer",
    "Breast Cancer",
    "Prostate Cancer",
    "Colorectal Cancer",
    "Leukemia",
    "Skin Cancer (Melanoma)",
    "Obesity",
    "Anemia",
    "Osteoporosis",
    "Migraine",
    "Gastro-esophageal Reflux Disease (GERD)"
};

int numDiseases = sizeof(diseases) / sizeof(diseases[0]);

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
    if (weekSchedule == NULL)
    {
        return NULL;
    }

    int mostShifts = CountShifts(GetMostBusyDoctor());
    int leastShifts = CountShifts(GetLeastBusyDoctor());
    double averageShifts = GetAverageNbShift();

    int shiftsCovered = GetNbShiftsCovered();
    double shiftsCoverage = ((double)shiftsCovered)/((double)GetTotalShifts());

    char buffer[512];

    sprintf(buffer, "The number of shifts covered for this week is %d, which correspond to a coverage of %.0f%% of all shifts.\nThe average number of shifts per doctor is %.1f.\nThe doctor with the most amount of shifts has %d shifts this week.\nThe doctor with the least amount of shifts has %d shifts this week.\n",
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


char* GetHospitalReport(char* username) {
    char bufferReport[4096];
    char bufferDate[40];
    char bufferTime[40];
    char bufferUsername[40];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    sprintf(bufferDate,"Date: [%d-0%d-0%d]\n",tm.tm_year+1900,tm.tm_mon+1,tm.tm_mday);
    sprintf(bufferTime,"Time: [%d:%d:%d]\n",tm.tm_hour, tm.tm_min, tm.tm_sec);
    sprintf(bufferUsername,"Generated By: [%s]\n\n\n",username);

    sprintf(bufferReport,"========================================\n"
                         "            HOSPITAL REPORT             \n"
                         "========================================\n");
    strcat(bufferReport,bufferDate);
    strcat(bufferReport,bufferTime);
    strcat(bufferReport,bufferUsername);

    strcat(bufferReport,"----------------------------------------\n"
                        "       DOCTOR UTILIZATION REPORT        \n"
                        "----------------------------------------\n\n"
                        "Doctor ID | Name            | Total Shifts | Morning | Afternoon | Evening\n"
                        "-------------------------------------------------------------------------\n");
    int count;
    char** reportBuffer = malloc(GetDoctorList()->length * sizeof(char*));
    GenerateDoctorReport(reportBuffer,&count);
    if (count == 0) {
        strcat(bufferReport,"NO DOCTOR DATA AVAILABLE FOR REPORTS\n\n");
    }
    else {
        for (int i = 0; i < count; i++) {
            strcat(bufferReport,reportBuffer[i]);
        }
    }

    char observationBuffer[OBSERVATION_BUFFER];
    GenerateObservations(count, observationBuffer);


    char patientReport[PATIENT_BUFFER];
    GeneratePatientsReport(patientReport);

    strcat(bufferReport,observationBuffer);
    strcat(bufferReport,patientReport);
    strcat(bufferReport,"========================================\n"
                        "              END OF REPORT             \n"
                        "========================================\n\n");


    char* result = calloc(strlen(bufferReport)+1, sizeof(char));

    strcpy(result, bufferReport);

    return result;
}


void GenerateDoctorReport(char** reportBuffer, int* count) {
    int index = 0;
    LL_Sentinel* current = GetDoctorList();

    if (!reportBuffer) {
        perror("Memory allocation failed");
    }

    for (size_t  i = 0 ; i< current->length; i++) {
        reportBuffer[index] = (char*)malloc(BUFFER_DOCTOR_SIZE);
        if (!reportBuffer[index]) {
            perror("Memory allocation failed");
        }
        doctor* currentDoctor = LL_Get(current, i);
        int totalShifts = currentDoctor->nbShift[0] + currentDoctor->nbShift[1] + currentDoctor->nbShift[2];

        snprintf(reportBuffer[index],BUFFER_DOCTOR_SIZE,
                "[%03d]     | %-15s | %-12d | %-7d | %-9d | %-6d\n",
                currentDoctor->id, currentDoctor->name, totalShifts,
                currentDoctor->nbShift[0], currentDoctor->nbShift[1], currentDoctor->nbShift[2]);
        index++;

    }
    *count = index; // Store the number of doctors stored

}

void GenerateObservations(int count, char *observationBuffer) {
    if (count == 0) {
        strcpy(observationBuffer, "No doctor data available for observations.\n");
        return;
    }

    LL_Sentinel* doctorList = GetDoctorList();

    doctor* firstDoc = LL_Get(doctorList, 0);
    int maxShifts = firstDoc->nbShift[0] + firstDoc->nbShift[1] + firstDoc->nbShift[2];
    int minShifts = firstDoc->nbShift[0] + firstDoc->nbShift[1] + firstDoc->nbShift[2];;
    int maxIndex = 0;
    int minIndex = 0;

    for (int i = 1; i < count; i++) {
        doctor* currentDoctor = LL_Get(doctorList, i);
        int totalShift = currentDoctor->nbShift[0] + currentDoctor->nbShift[1] + currentDoctor->nbShift[2];
        if (totalShift > maxShifts) {
            maxShifts = totalShift;
            maxIndex = i;
        }
        if (totalShift < minShifts) {
            minShifts = totalShift;
            minIndex = i;
        }
    }

    doctor* minDoctor = LL_Get(doctorList, minIndex);
    doctor* maxDoctor = LL_Get(doctorList, maxIndex);
    snprintf(observationBuffer, OBSERVATION_BUFFER,
             "\n\n\n- [%s has the highest shift count (%d shifts).]\n"
             "- [%s has fewer shifts (%d shifts); consider balancing workload.]\n",
             maxDoctor->name, maxShifts,
             minDoctor->name, minShifts);
}



void GeneratePatientsReport(char* patientBuffer) {
    int *diseaseHisto = calloc(numDiseases, sizeof(int));
    if (!diseaseHisto) {
        fprintf(stderr, "Error: Memory allocation failed for diseaseHisto\n");
        return;
    }

    LL_Sentinel* patientList = GetAllPatientsRecords();
    printf("Total Patients in List: %u\n", patientList->length);

    for (size_t i = 0; i < patientList->length; i++) {
        Patient* currentPatient = LL_Get(patientList, i);
        printf("Processing Patient %zu: Diagnosis = %s\n", i + 1, currentPatient->Diagnosis);

        for (int j = 0; j < numDiseases; j++) {
            if (strstr(currentPatient->Diagnosis, diseases[j]) != NULL) {
                diseaseHisto[j]++;
                printf(" - Matched Disease [%s]: Count = %d\n", diseases[j], diseaseHisto[j]);
            }
        }
    }

    // Print disease histogram before sorting
    printf("\nDisease Histogram:\n");
    for (int i = 0; i < numDiseases; i++) {
        printf("[%s]: %d occurrences\n", diseases[i], diseaseHisto[i]);
    }

    int index1 = 0, index2 = 0, index3 = 0;
    for (int i = 0; i < numDiseases; i++) {
        if (diseaseHisto[i] > diseaseHisto[index1]) {
            index3 = index2;
            index2 = index1;
            index1 = i;
        } else if (diseaseHisto[i] > diseaseHisto[index2]) {
            index3 = index2;
            index2 = i;
        } else if (diseaseHisto[i] > diseaseHisto[index3]) {
            index3 = i;
        }
    }

    printf("\nTop Diagnoses:\n");
    printf("1st: %s (%d occurrences)\n", diseases[index1], diseaseHisto[index1]);
    printf("2nd: %s (%d occurrences)\n", diseases[index2], diseaseHisto[index2]);
    printf("3rd: %s (%d occurrences)\n", diseases[index3], diseaseHisto[index3]);

    double firstPercentage = (patientList->length == 0) ? 0 : (double)diseaseHisto[index1] / patientList->length * 100;
    double secondPercentage = (patientList->length == 0) ? 0 : (double)diseaseHisto[index2] / patientList->length * 100;
    double thirdPercentage = (patientList->length == 0) ? 0 : (double)diseaseHisto[index3] / patientList->length * 100;

    sprintf(patientBuffer, "----------------------------------------\n"
                           "         PATIENT RECORD SUMMARY         \n"
                           "----------------------------------------\n\n");

    char patientinfoBuffer[150];
    sprintf(patientinfoBuffer, "Total Patients: [%d]\n"
                               "Discharged Patients: [%d]\n"
                               "Current Patients: [%d]\n\n",
            patientList->length + getNbDischarged(), getNbDischarged(), patientList->length);

    strcat(patientBuffer, patientinfoBuffer);

    char diseasesBuffer[150];
    sprintf(diseasesBuffer, "Top Diagnoses:\n"
                            "1. [%s] - [%.1f%%]\n"
                            "2. [%s] - [%.1f%%]\n"
                            "3. [%s] - [%.1f%%]\n\n",
            diseases[index1], firstPercentage,
            diseases[index2], secondPercentage,
            diseases[index3], thirdPercentage);

    strcat(patientBuffer, diseasesBuffer);

    free(diseaseHisto);
}
