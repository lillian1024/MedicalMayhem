#include <stdlib.h>
#include <string.h>
#include "patientUtil.h"
#include "../cmdUtil/cmdUtil.h"

LL_Sentinel* PatientList;

/// @brief Initialize the Patient list. This function must be called before any other functions in patientUtil.
void InitializePatientList()
{
    PatientList = LL_Create();
}

/// @brief Assigned the Patient list to an already created list.
/// @param list The list to assign PatientList to
void LoadPatientList(LL_Sentinel* list)
{
    PatientList = list;
}

/// @brief Dispose of the patient list. The InitializePatientList function must be called before calling any patient function after this function.
void DisposePatientList()
{
    LL_Dispose(PatientList);
}

/// @brief Safely add a new patient to the record (Patients array).
/// @param patientID Patient's ID
/// @param name Patient's Name
/// @param age Patient's Age
/// @param diagnosis Patient's Diagnosis
/// @param roomNumber Patient's Room Number
/// @return 1 if succefull, 0 if failed
int AddNewPatient(int patientID, char* name, int age, char* diagnosis, int roomNumber)
{
    if (GetPatientRecordByID(patientID) != NULL)
        return 0;
    
    if (age < MIN_PATIENT_AGE_YEARS)
        return 0;

    if (age > MAX_PATIENT_AGE_YEARS)
        return 0;

    if (name == NULL)
        return 0;

    Patient* newPatient = malloc(sizeof(Patient));

    if (newPatient == NULL)
        return 0;

    *newPatient = (Patient){
        patientID,
        name,
        age,
        diagnosis,
        roomNumber
    };

    LL_Append(PatientList, newPatient);

    return 1;
}

/// @brief Return a list of all recorded patients with max length MAX_NUMBER_PATIENTS.
/// @param patientLen (optionnal) valriable to store the returned list's length
/// @return A list of all recorded patients
LL_Sentinel* GetAllPatientsRecords()
{
    return PatientList;
}

Patient* GetPatientAtIndex(int index)
{
    return (Patient*)LL_Get(PatientList, index);
}

/// @brief Return a pointer to a Patient struct which as Patient.PatientID == patientID or NULL if not found.
/// @param patientID The ID of the patient to search
/// @return The found Patient or NULL
Patient* GetPatientRecordByID(int patientID)
{
    for (unsigned int i = 0; i < PatientList->length; i++)
    {
        Patient* patient = GetPatientAtIndex(i);
        if (patient->PatientID == patientID)
            return patient;
    }

    return NULL;
}

/// @brief Return a pointer to a Patient struct which as Patient.Name == patientName or NULL if not found.
/// @param patientID The name of the patient to search
/// @return The found Patient or NULL
Patient* GetPatientRecordByName(char* patientName)
{
    for (unsigned int i = 0; i < PatientList->length; i++)
    {
        Patient* patient = GetPatientAtIndex(i);
        if (strcmp(patient->Name, patientName) == 0)
            return patient;
    }

    return NULL;
}

/// @brief Discharge a patient, remove it from the patient list and free all resources used by this patient.
/// @param patient The patient to discharge
void DischargePatient(Patient* patient)
{
    for (unsigned int i = 0; i < PatientList->length; i++)
    {
        if (patient == GetPatientAtIndex(i))
        {
            LL_RemoveAt(PatientList, i);

            free(patient->Name);
            free(patient->Diagnosis);

            free(patient);

            return;
        }
    }
}
