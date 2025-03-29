#include <stdlib.h>
#include <stdio.h>
#include "managmentMenu.h"
#include "../../cmdUtil.h"
#include "../mainMenu/mainMenu.h"
#include "../../../reportUtil/reportUtil.h"

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
    
}

void ShowImportBackup()
{
    
}
