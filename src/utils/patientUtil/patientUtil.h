#include "../llistUtil/llist.h"

#ifndef PATIENT_UTIL_H
#define PATIENT_UTIL_H

#define MAX_NUMBER_PATIENTS 50

#define MIN_PATIENT_AGE_YEARS 0
#define MAX_PATIENT_AGE_YEARS 150

#define MIN_PATIENT_NAME_LENGTH 3
#define MAX_PATIENT_NAME_LENGTH 100
#define MIN_PATIENT_DIAGNOSIS_LENGTH 5
#define MAX_PATIENT_DIAGNOSIS_LENGTH 1000

typedef struct
{
    int PatientID;
    char* Name;
    int Age;
    char* Diagnosis;
    int RoomNumber;
}Patient;

void InitializePatientList();
void LoadPatientList(LL_Sentinel* list);
void DisposePatientList();
void DisposePatients(LL_Sentinel* list);

int AddNewPatient(int patientID, char* name, int age, char* diagnosis, int roomNumber);

LL_Sentinel* GetAllPatientsRecords();

Patient* GetPatientRecordByID(int patientID);
Patient* GetPatientRecordByName(char* patientName);
int getNbDischarged();
void setPatientDischarged(int nbPatientDischarged);
void DischargePatient(Patient* patient);

#endif
