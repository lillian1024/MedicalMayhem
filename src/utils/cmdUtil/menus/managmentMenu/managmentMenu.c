#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "managmentMenu.h"
#include "../../cmdUtil.h"
#include "../mainMenu/mainMenu.h"
#include "../../../reportUtil/reportUtil.h"
#include "../../../saveUtil/saveUtil.h"

void ShowDoctorReport();
void ShowEquipmentReport();
void ShowExportBackup();
void ShowImportBackup();

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
    printf("3. Export Backup\n");
    printf("4. Import Backup\n");
    printf("5. Back\n");
    printf("Select menu: ");
}

void ProcessManagmentMenuAction(int* appFlags)
{
    int menu = AskIntChoice(1, 5);
    
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
            ShowExportBackup();
            ShowManagmentMenu(1, appFlags);
            break;
        case 4:
            ShowImportBackup();
            ShowManagmentMenu(1, appFlags);
            break;
        case 5:
            ShowMainMenu(1, appFlags);
            break;
        default:
            printf("%sError in program!%s\n", TTYRED, TTYDEF);
            break;
    }
}

void SaveReport(char* report)
{
    char buffer[1024];

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

    LL_Sentinel* patientList = GetAllPatientsRecords();
    LL_Sentinel* doctorList = DoctorList;

    if (patientList)
        DisposePatientList();
    if (doctorList)
        DisposeDoctorList();

    if (!ReadSaveFile(dataPath, schedulePath, &patientList, &doctorList))
    {
        printf("%sUnable to import backup!%s\n", TTYRED, TTYDEF);
    }
    else
    {
        printf("%sBackup imported successfully!%s\n", TTYGRN, TTYDEF);
    }

    LoadPatientList(patientList);
    LoadDoctorList(doctorList);

    free(dataPath);
    free(schedulePath);
    free(path);

    getchar();
}
