#include <string.h>
#include "patientUtil.h"
#include "../cmdUtil/cmdUtil.h"

Patient Patients[MAX_NUMBER_PATIENTS];
int PatientsLen = 0;

/// @brief Safely add a new patient to the record (Patients array).
/// @param patientID Patient's ID
/// @param name Patient's Name
/// @param age Patient's Age
/// @param diagnosis Patient's Diagnosis
/// @param roomNumber Patient's Room Number
/// @return 1 if succefull, 0 if failed
int AddNewPatient(int patientID, char* name, int age, char* diagnosis, int roomNumber)
{
    if (PatientsLen == MAX_NUMBER_PATIENTS)
        return 0;

    if (GetPatientRecordByID(patientID) != NULL)
        return 0;
    
    if (age < MIN_PATIENT_AGE_YEARS)
        return 0;

    if (age > MAX_PATIENT_AGE_YEARS)
        return 0;

    if (name == NULL)
        return 0;

    Patient newPatient = {
        patientID,
        name,
        age,
        diagnosis,
        roomNumber
    };

    Patients[PatientsLen] = newPatient;

    PatientsLen++;

    return 1;
}

/// @brief Return a list of all recorded patients with max length MAX_NUMBER_PATIENTS.
/// @param patientLen (optionnal) valriable to store the returned list's length
/// @return A list of all recorded patients
Patient* GetAllPatientsRecords(int* patientLen)
{
    if (patientLen != NULL)
        *patientLen = PatientsLen;

    return Patients;
}

/// @brief Return a pointer to a Patient struct which as Patient.PatientID == patientID or NULL if not found.
/// @param patientID The ID of the patient to search
/// @return The found Patient or NULL
Patient* GetPatientRecordByID(int patientID)
{
    for (int i = 0; i < PatientsLen; i++)
    {
        if (Patients[i].PatientID == patientID)
            return Patients + i;
    }

    return NULL;
}

/// @brief Return a pointer to a Patient struct which as Patient.Name == patientName or NULL if not found.
/// @param patientID The name of the patient to search
/// @return The found Patient or NULL
Patient* GetPatientRecordByName(char* patientName)
{
    for (int i = 0; i < PatientsLen; i++)
    {
        if (strcmp(Patients[i].Name, patientName) == 0)
            return Patients + i;
    }

    return NULL;
}

void OffsetPatientRecord(int startingIndex, int offset)
{
    for (int i = startingIndex; i < PatientsLen; i++)
    {
        Patients[i - offset] = Patients[i];
    }
}

void DischargePatient(Patient* patient)
{
    for (int i = 0; i < PatientsLen; i++)
    {
        if (patient == (Patients + i))
        {
            OffsetPatientRecord(i+1, 1);

            PatientsLen--;

            return;
        }
    }
}
