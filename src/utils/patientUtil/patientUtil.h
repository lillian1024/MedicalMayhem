#ifndef PATIENT_UTIL_H
#define PATIENT_UTIL_H

#define MAX_NUMBER_PATIENTS 50

#define MIN_AGE_YEARS 0
#define MAX_AGE_YEARS 150

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
