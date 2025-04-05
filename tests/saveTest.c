#include <stdio.h>
#include <string.h>
#include "../src/utils/cmdUtil/cmdUtil.h"
#include "../src/utils/saveUtil/saveUtil.h"

/// @brief Test the save system
/// @return test success: 0, test failed !0
int main()
{
    char* defaultDataFilePath = "save_data.txt";
    char* defaultScheduleFilePath = "save_schudule.txt";
    char* outputDataFilePath = "output_data.txt";
    char* outputScheduleFilePath = "output_schudule.txt";

    char* defaultSaveDataFileContent = "NbPatient: 1\nNbDoctor: 2\nNbPatient Discharged: 1\n4|PatientFour|52|PatientFour's diagnosis|108\n0|DoctorSomething|1|2|3\n1|DoctorX|2|4|3\n";
    char* defaultSaveScheduleFileContent = "-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|\n";

    FILE* dataFile = fopen(defaultDataFilePath, "w");
    FILE* scheduleFile = fopen(defaultScheduleFilePath, "w");

    LL_Sentinel* patientList;
    LL_Sentinel* doctorList;

    fprintf(dataFile, "%s", defaultSaveDataFileContent);
    fprintf(scheduleFile, "%s", defaultSaveScheduleFileContent);

    fclose(dataFile);
    fclose(scheduleFile);

    ReadSaveFile(defaultDataFilePath, defaultScheduleFilePath, &patientList, &doctorList);

    WriteSaveFile(outputDataFilePath, outputScheduleFilePath, patientList, doctorList);

    DisposePatients(patientList);
    DisposeDoctors(doctorList);

    FILE* dataOutputFile = fopen(outputDataFilePath, "r");
    FILE* scheduleOutputFile = fopen(outputScheduleFilePath, "r");

    char dataBuffer[4096];
    char secondDataBuffer[256];
    char scheduleBuffer[4096];
    char secondscheduleBuffer[256];

    memset(dataBuffer, '\0', 1);
    memset(scheduleBuffer, '\0', 1);

    while (fscanf(dataOutputFile, "%[^\n]\n", secondDataBuffer) == 1)
    {
        strcat(dataBuffer, secondDataBuffer);
        strcat(dataBuffer, "\n");
    }

    while (fscanf(scheduleOutputFile, "%[^\n]\n", secondscheduleBuffer) == 1)
    {
        strcat(scheduleBuffer, secondscheduleBuffer);
        strcat(scheduleBuffer, "\n");
    }

    fclose(dataOutputFile);
    fclose(scheduleOutputFile);

    int dataDiff = strcmp(dataBuffer, defaultSaveDataFileContent);
    int scheduleDiff = strcmp(scheduleBuffer, defaultSaveScheduleFileContent);

    destoryWeekSchedule();

    remove(defaultDataFilePath);
    remove(defaultScheduleFilePath);
    remove(outputDataFilePath);
    remove(outputScheduleFilePath);

    return dataDiff || scheduleDiff;
}