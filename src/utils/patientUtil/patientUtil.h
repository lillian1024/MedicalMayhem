#ifndef PATIENT_UTIL_H
#define PATIENT_UTIL_H

#define MAX_NUMBER_PATIENTS 50

#define MIN_PATIENT_AGE_YEARS 0
#define MAX_PATIENT_AGE_YEARS 150

#define MIN_PATIENT_NAME_LENGTH 3
#define MAX_PATIENT_NAME_LENGTH 100
#define MIN_PATIENT_DIAGNOSIS_LENGTH 10
#define MAX_PATIENT_DIAGNOSIS_LENGTH 1000

typedef struct
{
    int PatientID;
    char* Name;
    int Age;
    char* Diagnosis;
    int RoomNumber;
}Patient;

int AddNewPatient(int patientID, char* name, int age, char* diagnosis, int roomNumber);

Patient* GetAllPatientsRecords(int* patientLen);

Patient* GetPatientRecordByID(int patientID);
Patient* GetPatientRecordByName(char* patientName);

void DischargePatient(Patient* patient);

#endif
