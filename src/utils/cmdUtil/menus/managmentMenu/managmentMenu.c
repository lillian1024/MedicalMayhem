#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "managmentMenu.h"
#include "../../cmdUtil.h"
#include "../mainMenu/mainMenu.h"
#include "../../../reportUtil/reportUtil.h"
#include "../../../saveUtil/saveUtil.h"
#include "../../../saveUtil/backupUtil.h"

void ShowDoctorReport();
void ShowEquipmentReport();
void ShowExportBackup();
void ShowImportBackup();
void ShowChangeRate();
void TurnOnOffAutomaticBackup();
void ShowFullReport(void);

void ShowManagmentMenu(int clearScreen, int* appFlags)
{
    (void)appFlags;

    if (clearScreen)
        clrscr();

    DisplayManagmentMenu();
    ProcessManagmentMenuAction(appFlags);
}

void DisplayManagmentMenu()
{
    printf("%s%sManagment Menu:%s%s\n", TTYGRN, TTYUNDER, TTYDEF, TTYNUND);
    printf("1. Show Doctor Report\n");
    printf("2. Show Equiment Report\n");
    printf("3. Show Full Report\n");
    printf("4. Export Backup\n");
    printf("5. Import Backup\n");
    printf("6. Change Backup Rate\n");
    printf("7. Turn On/Off Automatic Backup\n");
    printf("8. Back\n");
    printf("Select menu: ");
}



void ProcessManagmentMenuAction(int* appFlags)
{
    int menu = AskIntChoice(1, 8);
    
    switch (menu)
    {
        case 1:
            ShowDoctorReport();
            ShowManagmentMenu(1, appFlags);
            break;
        case 2:
            ShowEquipmentReport();
            ShowManagmentMenu(1, appFlags);
            break;
        case 3:
            ShowFullReport();
            ShowManagmentMenu(1, appFlags);
            break;
        case 4:
            ShowExportBackup();
            ShowManagmentMenu(1, appFlags);
            break;
        case 5:
            ShowImportBackup();
            ShowManagmentMenu(1, appFlags);
            break;
        case 6:
            ShowChangeRate();
            ShowManagmentMenu(1, appFlags);
            break;
        case 7:
            TurnOnOffAutomaticBackup();
            ShowManagmentMenu(1, appFlags);
            break;
        case 8:
            ShowMainMenu(1, appFlags);
            break;
        default:
            printf("%sError in program!%s\n", TTYRED, TTYDEF);
            break;
    }
}

void SaveReport(char* report)
{
    char buffer[4096];

    printf("Please input the path of the report file: ");
    AskStr(buffer, 5, 1024);

    FILE* reportFile = fopen(buffer, "w");

    if (reportFile == NULL)
    {
        clrscr();

        printf("%sUnable to write report file!%s\n", TTYRED, TTYDEF);

        getchar();

        return;
    }

    fprintf(reportFile, "%s", report);

    fclose(reportFile);
}

void ShowDoctorReport()
{
    char* report = GetDoctorReport();

    clrscr();

    if (weekSchedule == NULL)
    {
        printf("%sUnable to generate report: %sWeek schedule not generated!\n", TTYRED, TTYDEF);

        getchar();

        return;
    }

    printf("%sDoctor report:%s\n%s\n", TTYUNDER, TTYNUND, report);

    printf("Do you want to save this report to a file? (1:yes, 2:no) ");
    int choice = AskIntChoice(1, 2);

    if (choice == 1)
    {
        SaveReport(report);
    }

    free(report);

    return;
}

void ShowEquipmentReport()
{
    char* report = GetEquipmentReport();

    clrscr();

    printf("%sEquipment report:%s\n%s\n", TTYUNDER, TTYNUND, report);

    printf("Do you want to save this report to a file? (1:yes, 2:no) ");
    int choice = AskIntChoice(1, 2);

    if (choice == 1)
    {
        SaveReport(report);
    }

    free(report);

    return;
}

void ShowFullReport() {
    char username[MAX_NAME_LEN];
    printf("Please input your username: ");
    AskStr(username, 2, 1024);

    char* report = GetHospitalReport(username);

    clrscr();

    printf("%s",report);

    printf("Do you want to save this report to a file? (1:yes, 2:no) ");
    int choice = AskIntChoice(1, 2);

    if (choice == 1)
    {
        SaveReport(report);
    }

    free(report);

    return;
}

void ShowExportBackup()
{
    clrscr();

    int bufferSize = 1024;

    char buffer[bufferSize];

    printf("Please input the path and name of the backup files (without extension): ");
    AskStr(buffer, 5, bufferSize);

    int pathLength = strlen(buffer);

    char* path = calloc(pathLength + 1, sizeof(char));

    strcpy(path, buffer);

    char* dataPath = calloc(pathLength + strlen(backupDataSubPath) + 1, sizeof(char));
    char* schedulePath = calloc(pathLength + strlen(backupScheduleSubPath) + 1, sizeof(char));

    strcpy(dataPath, path);
    strcpy(schedulePath, path);

    strcat(dataPath, backupDataSubPath);
    strcat(schedulePath, backupScheduleSubPath);

    if (!WriteSaveFile(dataPath, schedulePath, GetAllPatientsRecords(), DoctorList))
    {
        printf("%sUnable to save backup!%s\n", TTYRED, TTYDEF);
    }
    else
    {
        printf("%sBackup saved successfully!%s\n", TTYGRN, TTYDEF);
    }

    free(dataPath);
    free(schedulePath);
    free(path);

    getchar();
}

void ShowImportBackup()
{
    clrscr();

    int bufferSize = 1024;

    char buffer[bufferSize];

    printf("Please input the path and name of the backup files (without extension): ");
    AskStr(buffer, 5, bufferSize);

    int pathLength = strlen(buffer);

    char* path = calloc(pathLength + 1, sizeof(char));

    strcpy(path, buffer);

    char* dataPath = calloc(pathLength + strlen(backupDataSubPath) + 1, sizeof(char));
    char* schedulePath = calloc(pathLength + strlen(backupScheduleSubPath) + 1, sizeof(char));

    strcpy(dataPath, path);
    strcpy(schedulePath, path);

    strcat(dataPath, backupDataSubPath);
    strcat(schedulePath, backupScheduleSubPath);

    LL_Sentinel* patientList = LL_Create();
    LL_Sentinel* doctorList = LL_Create();

    if (!ReadSaveFile(dataPath, schedulePath, &patientList, &doctorList))
    {
        LL_Dispose(patientList);
        LL_Dispose(doctorList);

        printf("%sUnable to import backup!%s\n", TTYRED, TTYDEF);
    }
    else
    {
        printf("%sBackup imported successfully!%s\n", TTYGRN, TTYDEF);

        DisposePatientList();
        DisposeDoctorList();

        LoadPatientList(patientList);
        LoadDoctorList(doctorList);
    }

    free(dataPath);
    free(schedulePath);
    free(path);

    getchar();
}

void ShowChangeRate()
{

    clrscr();

    printf("Enter New Backup Rate(value in minute): ");
    int choice = AskIntChoice(1, 10);
    SetBackupInterval(choice*60);
    return;
}

void TurnOnOffAutomaticBackup() {
    clrscr();
    printf("Do you want to turn On or Off automatic backup (1:ON, 2:OFF) ");
    int choice = AskIntChoice(1, 2);
    if (choice == 1) {
        EnableBackup();
    }
    else {
        DisableBackup();
    }

}