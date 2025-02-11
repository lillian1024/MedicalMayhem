#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patientMenu.h"
#include "../../cmdUtil.h"
#include "../../../patientUtil/patientUtil.h"
#include "../mainMenu/mainMenu.h"
#include "../doctorMenu/doctorMenu.h"
#include "../scheduleMenu/scheduleMenu.h"

void ShowPatientAdd();
Patient* ShowPatientSelection();
void ShowPatientRecords(Patient* patient);
void ShowPatientRecord();
void ShowAllPatientRecords();
void ShowDischargePatient();

void ShowPatientMenu(int clearScreen, int* appFlags)
{
    (void)appFlags;

    if (clearScreen)
        clrscr();

    DisplayPatientMenu();
    ProcessPatientMenuAction(appFlags);
}

void DisplayPatientMenu()
{
    printf("%s%sPatient Menu:%s%s\n", TTYGRN, TTYUNDER, TTYDEF, TTYNUND);
    printf("1. Add new patient\n");
    printf("2. View patient records\n");
    printf("3. View all patients records\n");
    printf("4. Discharge patient\n");
    printf("5. Back\n");
    printf("Select menu: ");
}

void ProcessPatientMenuAction(int* appFlags)
{
    int menu = AskIntChoice(1, 5);
    
    switch (menu)
    {
        case 1:
            ShowPatientAdd();
            ShowPatientMenu(1, appFlags);
            break;
        case 2:
            ShowPatientRecord();
            ShowPatientMenu(1, appFlags);
            break;
        case 3:
            ShowAllPatientRecords();
            ShowPatientMenu(1, appFlags);
            break;
        case 4:
            ShowDischargePatient();
            ShowPatientMenu(1, appFlags);
            break;
        case 5:
            ShowMainMenu(1, appFlags);
            break;
        default:
            printf("%sError in program!%s", TTYRED, TTYDEF);
            break;
    }
}

void ShowPatientAdd()
{
    clrscr();

    int patientID, age, roomNumber;
    char name[MAX_PATIENT_NAME_LENGTH];
    char diagnosis[MAX_PATIENT_DIAGNOSIS_LENGTH];

    printf("Please input the ID of the patient: ");
    scanf("%d", &patientID);
    flushSTDIN();

    printf("Please input the name of the patient: ");
    AskStr(name, MIN_PATIENT_NAME_LENGTH, MAX_PATIENT_NAME_LENGTH);

    printf("Please input the age of the patient: ");
    age = AskIntChoice(MIN_PATIENT_AGE_YEARS, MAX_PATIENT_AGE_YEARS);

    printf("Please input the diagnosis of the patient: ");
    AskStr(diagnosis, MIN_PATIENT_DIAGNOSIS_LENGTH, MAX_PATIENT_DIAGNOSIS_LENGTH);

    printf("Please input the roomNumber of the patient: ");
    scanf("%d", &roomNumber);
    flushSTDIN();

    char* newName = calloc(strlen(name), sizeof(char));
    strcpy(newName, name);

    char* newDiagnosis = calloc(strlen(diagnosis), sizeof(char));
    strcpy(newDiagnosis, diagnosis);

    AddNewPatient(patientID, newName, age, newDiagnosis, roomNumber);
}

Patient* ShowPatientSelection()
{
    clrscr();

    printf("Choose a method to select patient: 1:name, 2:id ");
    int choice = AskIntChoice(1, 2);

    if (choice == 1)
    {
        //Name selection
        char name[MAX_PATIENT_NAME_LENGTH];

        printf("Please input the name of the patient: ");
        AskStr(name, MIN_PATIENT_NAME_LENGTH, MAX_PATIENT_NAME_LENGTH);

        return GetPatientRecordByName(name);
    }
    else
    {
        //Id selection
        int id;

        printf("Please input the id of the patient: ");
        scanf("%d", &id);
        flushSTDIN();

        return GetPatientRecordByID(id);
    }
}

void ShowPatientRecords(Patient* patient)
{
    printf("Patient %d\n", patient->PatientID);
    printf("Name: %s\n", patient->Name);
    printf("Age: %d\n", patient->Age);
    printf("Diagnosis: %s\n", patient->Diagnosis);
    printf("Room number: %d\n", patient->RoomNumber);
}

void ShowPatientRecord()
{
    clrscr();

    Patient* patient = ShowPatientSelection();

    if (patient == NULL)
        return;

    clrscr();

    ShowPatientRecords(patient);

    getchar();
}

void ShowAllPatientRecords()
{
    clrscr();

    int patientLen;

    Patient* patients = GetAllPatientsRecords(&patientLen);

    if (patientLen <= 0)
    {
        printf("No patients found!");

        getchar();

        return;
    }
    
    for (int i = 0; i < patientLen; i++)
    {
        ShowPatientRecords(patients + i);
    }

    getchar();
}

void ShowDischargePatient()
{
    Patient* patient = ShowPatientSelection();

    DischargePatient(patient);
}
