#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "saveUtil.h"

#ifdef WIN32
#include <io.h>
#define R_OK 4
#define access _access
char separator = '\\';
#else
#include <unistd.h>
char separator = '/';
#endif

char* appDirectory;

const char* saveDataSubPath = "/saveData.txt";
char* saveDataPath;

const char* saveScheduleSubPath = "/saveSchedule.txt";
char* saveSchedulePath;

const char* backupDataSubPath = "_data.txt";
const char* backupScheduleSubPath = "_schedule.txt";

int nbPatients;
int nbDoctor;

int CanLoad(char* filepath)
{
    return access(filepath, R_OK) == 0;
}

void LoadAppDirectory(const char* appPath) {
    char* slash = strrchr(appPath, separator);

    int length = slash - appPath;

    appDirectory = calloc(length + 1, sizeof(char));

    strncpy(appDirectory, appPath, length);
}

char* GetSaveDataPath()
{
    int saveDataPathLength;

    saveDataPathLength = strlen(appDirectory) + strlen(saveDataSubPath) + 1;

    char* dataPath = calloc(saveDataPathLength, sizeof(char));

    if (dataPath == NULL)
    {
        return NULL;
    }

    strcpy(dataPath, appDirectory);
    strcat(dataPath, saveDataSubPath);

    return dataPath;
}

char* GetSaveSchedulePath(const char* appPath)
{
    int saveSchedulePathLength;

    saveSchedulePathLength = strlen(appPath) + strlen(saveScheduleSubPath) + 1;

    char* schedulePath = calloc(saveSchedulePathLength, sizeof(char));

    if (schedulePath == NULL)
    {
        return NULL;
    }

    strcpy(schedulePath, appPath);
    strcat(schedulePath, saveScheduleSubPath);

    return schedulePath;
}

void LoadSavePaths(const char* appPath)
{
    saveDataPath = GetSaveDataPath(appPath);
    saveSchedulePath = GetSaveSchedulePath(appPath);
}

//Writing save file

char* GetSaveMetaDataLines(int nbPatient, int nbDoctor, char* result)
{
    sprintf(result, "NbPatient: %d\nNbDoctor: %d\n", nbPatient, nbDoctor);

    return result;
}

char* GetPatientDataLine(const Patient* patient, char* result)
{
    sprintf(result, "%d|%s|%d|%s|%d", patient->PatientID, patient->Name, patient->Age, patient->Diagnosis, patient->RoomNumber);

    return result;
}

char* GetDoctorDataLine(const doctor* doctorStruct, char* result)
{
    sprintf(result, "%d|%s|%d|%d|%d", doctorStruct->id, doctorStruct->name, doctorStruct->nbShift[0], doctorStruct->nbShift[1], doctorStruct->nbShift[2]);

    return result;
}

void WriteScheduleToFile(FILE* file, int** schedule)
{
    if (!schedule)
    {
        return;
    }

    for (int i = 0; i < DAYS; i++) 
    {
        for (int j = 0; j < SHIFTS; j++) 
        {
            fprintf(file, "%d|", schedule[i][j]);
        }
    }
    fprintf(file, "\n");
}

int WriteSaveFile(char* dataFilePath, char* scheduleFilePath, LL_Sentinel* patientList, LL_Sentinel* doctorList)
{
    FILE* dataFile = fopen(dataFilePath, "w");
    FILE* scheduleFile = fopen(scheduleFilePath, "w");

    if (dataFile == NULL)
    {
        printf("error opening data file\n");
        return 0;
    }

    char metaDataStr[100];
    GetSaveMetaDataLines(patientList->length, doctorList->length, metaDataStr);

    fprintf(dataFile, "%s", metaDataStr);

    for (unsigned int i = 0; i < patientList->length; i++)
    {
        char patientStr[256];
        GetPatientDataLine((Patient*)LL_Get(patientList, i), patientStr);

        fprintf(dataFile, "%s\n", patientStr);
    }

    for (unsigned int i = 0; i < doctorList->length; i++)
    {
        char doctorStr[256];
        GetDoctorDataLine((doctor*)LL_Get(doctorList, i), doctorStr);

        fprintf(dataFile, "%s\n", doctorStr);
    }

    WriteScheduleToFile(scheduleFile, weekSchedule);

    fclose(dataFile);
    fclose(scheduleFile);

    return 1;
}

//Reading save file

int GetSaveMetaData(FILE* file, int* nbPatient, int* nbDoctor)
{
    return fscanf(file, "NbPatient: %d\nNbDoctor: %d\n", nbPatient, nbDoctor) == 2;
}

int GetPatientFromLine(Patient* patient, char* line)
{
    int id, age, room;
    char name[MAX_PATIENT_NAME_LENGTH];
    char diagnosis[MAX_PATIENT_DIAGNOSIS_LENGTH];

    int value = sscanf(line, "%d|%[^|]|%d|%[^|]|%d", &id, name, &age, diagnosis, &room);

    if (value != 5)
    {
        return 0;
    }

    char* mallocName = calloc(strlen(name)+1, sizeof(char));
    char* mallocDiagnosis = calloc(strlen(diagnosis)+1, sizeof(char));

    strcpy(mallocName, name);
    strcpy(mallocDiagnosis, diagnosis);

    *patient = (Patient){
        id,
        mallocName,
        age,
        mallocDiagnosis,
        room,
    };

    return 1;
}

int GetDoctorFromLine(doctor* doctorStruct, char* line)
{
    int id, nbMorningShifts, nbAfternoonShifts, nbEveningShifts;
    char name[MAX_PATIENT_NAME_LENGTH];

    int value = sscanf(line, "%d|%[^|]|%d|%d|%d", &id, name, &nbMorningShifts, &nbAfternoonShifts, &nbEveningShifts);

    if (value != 5)
    {
        return 0;
    }

    char* mallocName = calloc(strlen(name)+1, sizeof(char));

    strcpy(mallocName, name);

    int nbShifts[3];

    nbShifts[0] = nbMorningShifts;
    nbShifts[1] = nbAfternoonShifts;
    nbShifts[2] = nbEveningShifts;

    doctorStruct->id = id;
    doctorStruct->name = mallocName;
    doctorStruct->nbShift[0] = nbShifts[0];
    doctorStruct->nbShift[1] = nbShifts[1];
    doctorStruct->nbShift[2] = nbShifts[2];

    return 1;
}

int ReadAllPatients(FILE* file, int nbPatient, LL_Sentinel* patientList)
{
    for (int i = 0; i < nbPatient; i++)
    {
        char patientLine[2048];

        //File format error
        if (fscanf(file, "%[^\n]\n", patientLine) != 1)
        {
            return 0;
        }

        Patient* currentPatient = malloc(sizeof(Patient));

        //Allocation error
        if (!currentPatient)
        {
            return 0;
        }

        //Patient line format error
        if (!GetPatientFromLine(currentPatient, patientLine))
        {
            return 0;
        }

        LL_Append(patientList, currentPatient);
    }

    return 1;
}

int ReadAllDoctors(FILE* file, int nbDoctor, LL_Sentinel* doctorList)
{
    for (int i = 0; i < nbDoctor; i++)
    {
        char doctorLine[2048];

        //File format error
        if (fscanf(file, "%[^\n]\n", doctorLine) != 1)
        {
            return 0;
        }

        doctor* currentDoctor = malloc(sizeof(doctor));

        //Allocation error
        if (!currentDoctor)
        {
            return 0;
        }

        //Doctor line format error
        if (!GetDoctorFromLine(currentDoctor, doctorLine))
        {
            return 0;
        }

        LL_Append(doctorList, currentDoctor);
    }

    return 1;
}

int ReadScheduleFromFile(FILE* file, int*** schedule)
{
    *schedule = createSchedule();

    for (int i = 0; i < DAYS; i++) 
    {
        for (int j = 0; j < SHIFTS; j++) 
        {
            int id;

            if (fscanf(file, "%d|", & id) != 1)
            {
                return 0;
            }

            (*schedule)[i][j] = id;
        }
    }

    return 1;
}

int ReadSaveFile(char* dataFilePath, char* scheduleFilePath, LL_Sentinel** patientList, LL_Sentinel** doctorList)
{
    FILE* dataFile = fopen(dataFilePath, "r");
    FILE* scheduleFile = fopen(scheduleFilePath, "r");
    
    if (!dataFile)
    {
        return 0;
    }

    int nbPatient, nbDoctor;

    if (!GetSaveMetaData(dataFile, &nbPatient, &nbDoctor))
    {
        return 0;
    }

    *patientList = LL_Create();

    if (!*patientList)
    {
        return 0;
    }

    if (!ReadAllPatients(dataFile, nbPatient, *patientList))
    {
        LL_Dispose(*patientList);

        return 0;
    }

    *doctorList = LL_Create();

    if (!*doctorList)
    {
        LL_Dispose(*patientList);

        return 0;
    }

    if (!ReadAllDoctors(dataFile, nbDoctor, *doctorList))
    {
        LL_Dispose(*patientList);

        return 0;
    }

    if (!ReadScheduleFromFile(scheduleFile, &weekSchedule))
    {
        return 0;
    }

    fclose(dataFile);
    fclose(scheduleFile);

    return 1;
}
